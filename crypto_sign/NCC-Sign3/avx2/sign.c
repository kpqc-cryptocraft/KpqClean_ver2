#include <stdint.h>
#include "params.h"
#include "sign.h"
#include "packing.h"
#include "poly.h"
#include "randombytes.h"
#include "symmetric.h"
#include "fips202.h"
#include "stdio.h"
#include "cpucycles.h"
#include <stdlib.h>

#define NTT 1
#define AVX 1
#define CYCLE 0
#if CYCLE==1
extern t_notmul;
extern t_mul;
extern t_overhead;
#endif

uint64_t mask_ar[4]={~(0UL)};

void print_256(__m256i a)
{
    int32_t* a_32 = (int32_t*) &a;
    printf("%8x %8x %8x %8x %8x %8x %8x %8x\n", a_32[7], a_32[6], a_32[5], a_32[4], a_32[3], a_32[2], a_32[1], a_32[0]);
}

void print_256_N_avx(__m256i a[N_avx])
{
    for(int i = 0 ; i < N_avx ; i++)
    {
	print_256(a[i]);
    }
}

int crypto_sign_keypair(uint8_t *pk, uint8_t *sk)
{
	uint8_t zeta[SEEDBYTES];
	uint8_t seedbuf[3 * SEEDBYTES];
	uint8_t tr[SEEDBYTES];
	const uint8_t *xi_1, *xi_2, *key;

	__m256i mat[N_avx] = {0};
	poly s1, s2, t1, t0;

#if CYCLE==1
	uint64_t tt1 = cpucycles();
#endif

	randombytes(zeta, SEEDBYTES);
	randombytes(seedbuf, SEEDBYTES);
	shake256(seedbuf, 3 * SEEDBYTES, seedbuf, SEEDBYTES);
	xi_1 = seedbuf;
	xi_2 = seedbuf + SEEDBYTES;
	key = seedbuf + 2 * SEEDBYTES;
	poly_uniform_avx_4way(mat,zeta,0);
	poly_uniform_eta(&s1, xi_1, 0);
	poly_uniform_eta(&s2, xi_2, 0);

#if CYCLE==1
	uint64_t tt2=cpucycles();
	t_notmul+=tt2-tt1-t_overhead;
#endif

	__m256i temp[T_avx];
	__m256i temp_3x[N_avx];
	ntt_avx_4way(temp, s1.coeffs);
	poly_base_mul_avx_4way(temp_3x, temp, mat);
	invntt_tomont_avx_4way(t1.coeffs, temp_3x);

#if CYCLE==1
	tt1=cpucycles();

	t_mul+=tt1-tt2-t_overhead;
#endif


	poly_add(&t1, &t1, &s2);
	poly_caddq(&t1);

	poly_power2round(&t1, &t0, &t1);

	pack_pk(pk, zeta, &t1);

	shake256(tr, SEEDBYTES, pk, CRYPTO_PUBLICKEYBYTES);

	pack_sk(sk, zeta, tr, key, &t0, &s1, &s2);


#if CYCLE==1
	t_notmul+=cpucycles()-tt1-t_overhead;
#endif

	return 0;
}

int crypto_sign_signature(uint8_t *sig,
                        	size_t *siglen,
                        	const uint8_t *m,
                        	size_t mlen,
                        	const uint8_t *sk)
{
	unsigned int n;
	uint8_t seedbuf[3 * SEEDBYTES + 2 * CRHBYTES];
	uint8_t *zeta, *tr, *key, *mu, *rho;
	uint16_t nonce = 0;
	poly s1, y, z, t0, s2, w1, w0, h;
	poly cp;
	__m256i mat[T_avx]={0};

	keccak_state state;

	zeta = seedbuf;
	tr = zeta + SEEDBYTES;
	key = tr + SEEDBYTES;
	mu = key + SEEDBYTES;
	rho = mu + CRHBYTES;
	unpack_sk(zeta, tr, key, &t0, &s1, &s2, sk);

	shake256_init(&state);
	shake256_absorb(&state, tr, SEEDBYTES);
	shake256_absorb(&state, m, mlen);
	shake256_finalize(&state);
	shake256_squeeze(mu, CRHBYTES, &state);

#ifdef NIMS_RANDOMIZED_SIGNING
	randombytes(rho, CRHBYTES);
#else
	shake256(rho, CRHBYTES, key, SEEDBYTES + CRHBYTES);
#endif
	poly_uniform_avx_4way(mat,zeta,0);

	__m256i s1_avx[T_avx],s2_avx[T_avx],t0_avx[T_avx];
	ntt_avx_4way(s1_avx, s1.coeffs);
	ntt_avx_4way(s2_avx, s2.coeffs);
	ntt_avx_4way(t0_avx, t0.coeffs);

rej:
	poly_uniform_gamma1(&y, rho, nonce++);
	z = y;

	__m256i z_avx[N_avx],w1_3x[N_avx];
	ntt_avx_4way(z_avx, z.coeffs);
	poly_base_mul_avx_4way(w1_3x, z_avx, mat);
	invntt_tomont_avx_4way(w1.coeffs, w1_3x);

	poly_decompose(&w1, &w0, &w1);

	polyw1_pack(sig, &w1);

	shake256_init(&state);
	shake256_absorb(&state, mu, CRHBYTES);
	shake256_absorb(&state, sig, POLYW1_PACKEDBYTES);
	shake256_finalize(&state);
	shake256_squeeze(sig, SEEDBYTES, &state);
	poly_challenge(&cp, sig);

	__m256i cp_avx[T_avx];
	ntt_avx_4way(cp_avx, cp.coeffs);
	poly_base_mul_avx_4way(z_avx, cp_avx, s1_avx);
	invntt_tomont_avx_4way(z.coeffs, z_avx);

	poly_add(&z, &z, &y);
  	poly_reduce(&z);
	if(poly_chknorm(&z, GAMMA1 - BETA))
	{
		goto rej;
	}
	
	__m256i h_avx[N_avx];
	poly_base_mul_avx_4way(h_avx, cp_avx, s2_avx);
	invntt_tomont_avx_4way(h.coeffs, h_avx);

	poly_sub(&w0, &w0, &h);
  	poly_reduce(&w0);


	if(poly_chknorm(&w0, GAMMA2 - BETA))
	{
		goto rej;
	}

	poly_base_mul_avx_4way(h_avx, cp_avx, t0_avx);
	invntt_tomont_avx_4way(h.coeffs, h_avx);

  	poly_reduce(&h);
	if(poly_chknorm(&h, GAMMA2))
	{
		goto rej;
	}

	poly_add(&w0, &w0, &h);

	n = poly_make_hint(&h, &w0, &w1);

	if(n > OMEGA)
	{
		goto rej;
	}

	pack_sig(sig, sig, &z, &h);
	*siglen = CRYPTO_BYTES;
	return 0;
}

int crypto_sign(uint8_t *sm,
              	size_t *smlen,
              	const uint8_t *m,
              	size_t mlen,
              	const uint8_t *sk)
{
	size_t i;

	for(i = 0; i < mlen ; i++)
		sm[CRYPTO_BYTES + mlen - 1 - i] = m[mlen - 1 - i];
	crypto_sign_signature(sm, smlen, sm + CRYPTO_BYTES, mlen, sk);
	*smlen += mlen;
	return 0;
}


int crypto_sign_verify(const uint8_t *sig,
                       size_t siglen,
                       const uint8_t *m,
                       size_t mlen,
                       const uint8_t *pk)
{
	unsigned int i;
	uint8_t buf[POLYW1_PACKEDBYTES];
	uint8_t zeta[SEEDBYTES];
	uint8_t mu[CRHBYTES];
	uint8_t c[SEEDBYTES];
	uint8_t c2[SEEDBYTES];

	poly cp, z, t1, w1, h;
	__m256i mat[T_avx]={0};
	keccak_state state;

	if(siglen != CRYPTO_BYTES)
		return -1;
	unpack_pk(zeta, &t1, pk);

	if(unpack_sig(c, &z, &h, sig))
		return -1;

	if(poly_chknorm(&z, GAMMA1 - BETA))
		return -1;

	shake256(mu, SEEDBYTES, pk, CRYPTO_PUBLICKEYBYTES);
	shake256_init(&state);
	shake256_absorb(&state, mu, SEEDBYTES);
	shake256_absorb(&state, m, mlen);
	shake256_finalize(&state);
	shake256_squeeze(mu, CRHBYTES, &state);
	poly_challenge(&cp, c);

	poly_uniform_avx_4way(mat,zeta,0);

	__m256i z_avx[T_avx], w1_avx[N_avx];
	ntt_avx_4way(z_avx, z.coeffs);
	poly_base_mul_avx_4way(w1_avx, z_avx, mat);
	invntt_tomont_avx_4way(w1.coeffs, w1_avx);

	poly_shiftl(&t1);

	__m256i t1_avx[T_avx], cp_avx[T_avx], t1_3x[N_avx];
	ntt_avx_4way(t1_avx, t1.coeffs);
	ntt_avx_4way(cp_avx, cp.coeffs);
	poly_base_mul_avx_4way(t1_3x, cp_avx, t1_avx);
	invntt_tomont_avx_4way(t1.coeffs, t1_3x);

	poly_sub(&w1, &w1, &t1);
	poly_caddq(&w1);

	poly_use_hint(&w1, &w1, &h);	
	polyw1_pack(buf, &w1);

	shake256_init(&state);
	shake256_absorb(&state, mu, CRHBYTES);
	shake256_absorb(&state, buf, POLYW1_PACKEDBYTES);
	shake256_finalize(&state);
	shake256_squeeze(c2, SEEDBYTES, &state);

	for(i = 0 ; i < SEEDBYTES ; i++)
		if(c[i] != c2[i])
			return -1;

	return 0;
}

int crypto_sign_open(uint8_t *m,
                     size_t *mlen,
                     const uint8_t *sm,
                     size_t smlen,
                     const uint8_t *pk)
{
	size_t i;

	if(smlen < CRYPTO_BYTES)
		goto badsig;

	*mlen = smlen - CRYPTO_BYTES;
	if(crypto_sign_verify(sm, CRYPTO_BYTES, sm + CRYPTO_BYTES, *mlen, pk))
		goto badsig;
	else
	{
		for(i = 0; i < *mlen ; i++)
			m[i] = sm[CRYPTO_BYTES + i];
		return 0;
	}

badsig:
	/* Signature verification failed */
	*mlen = -1;
	for(i = 0 ; i < smlen ; i++)
		m[i] = 0;

	return -1;
}
