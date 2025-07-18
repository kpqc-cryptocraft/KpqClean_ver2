#include "indcpa.h"
#include "align.h"
#include "cbd.h"
#include "randombytes.h"
#include "../../../common/Keccak_avx2/fips202.h"

/*************************************************
 * Name:        genRx_vec
 *
 * Description: Deterministically generate a vector of sparse polynomial r(x)
 *              from a seed.
 *
 * Arguments:   - polyvec *r: pointer to ouptput vector r
 *              - uint8_t *input: pointer to input seed (of length input_size)
 **************************************************/
void genRx_vec(polyvec *r, const uint8_t *input) {
    unsigned int i;
    ALIGNED_UINT8(CBDSEED_BYTES) buf[4];

    __m256i f = _mm256_loadu_si256((__m256i *)input);
    _mm256_store_si256(buf[0].vec, f);
    _mm256_store_si256(buf[1].vec, f);
    _mm256_store_si256(buf[2].vec, f);
    _mm256_store_si256(buf[3].vec, f);
    buf[0].coeffs[32] = 0;
    buf[1].coeffs[32] = 1;
    buf[2].coeffs[32] = 2;
    buf[3].coeffs[32] = 3;
#if DELTA_BYTES != 32
#error "This function assumes DELTA_BYTES to be 32."
#endif
    shake256x4(buf[0].coeffs, buf[1].coeffs, buf[2].coeffs, buf[3].coeffs,
               CBDSEED_BYTES, buf[0].coeffs, buf[1].coeffs, buf[2].coeffs,
               buf[3].coeffs, DELTA_BYTES + 1);
#if MODULE_RANK > 4
#error "This function works only up to MODULE_RANK = 4."
#endif
    for (i = 0; i < MODULE_RANK; ++i) {
        poly_cbd(&r->vec[i], buf[i].CBDSEED_FIELD);
    }
}

/*************************************************
 * Name:        indcpa_keypair
 *
 * Description: Generates public and private key for the CPA-secure
 *              Module-Lizard public-key encryption scheme.
 *
 * Arguments:   - public_key *pk: pointer to output public key
 *                (a structure composed of (seed of A, matrix A, vector b))
 *              - secret_key *sk: pointer to output private key
 *                (a structure composed of (vector s, t, vector negstart))
 **************************************************/
void indcpa_keypair(uint8_t pk[PUBLICKEY_BYTES],
                    uint8_t sk[PKE_SECRETKEY_BYTES]) {
    public_key pk_tmp;
    secret_key sk_tmp;
    memset(&pk_tmp, 0, sizeof(public_key));
    memset(&sk_tmp, 0, sizeof(secret_key));

    uint8_t seed[CRYPTO_BYTES + PKSEED_BYTES] = {0};
    randombytes(seed, CRYPTO_BYTES);
#if CRYPTO_BYTES + PKSEED_BYTES != 64
#error "This implementation assumes CRYPTO_BYTES + PKSEED_BYTES to be 64"
#endif
    sha3_512(seed, seed, CRYPTO_BYTES);

    genSx_vec(&sk_tmp, seed);

    memcpy(&pk_tmp.seed, seed + CRYPTO_BYTES, PKSEED_BYTES);
    genPubkey(&pk_tmp, &sk_tmp, seed);

    memset(pk, 0, PUBLICKEY_BYTES);
    memset(sk, 0, PKE_SECRETKEY_BYTES);
    save_to_string_pk(pk, &pk_tmp);
    save_to_string_sk(sk, &sk_tmp);
}

/*************************************************
 * Name:        indcpa_enc
 *
 * Description: Encryption function of the CPA-secure
 *              Module-Lizard public-key encryption scheme.
 *
 * Arguments:   - ciphertext *ctxt: pointer to output ciphertext
 *                (a structure composed of (vector c1, c2))
 *              - public_key *pk: pointer to input public key
 *                (a structure composed of (seed of A, matrix A, vector b))
 *              - uint8_t *delta: pointer to input random delta (of length
 *                DELTA_BYTES) to deterministically generate all randomness
 **************************************************/
void indcpa_enc(uint8_t ctxt[CIPHERTEXT_BYTES],
                const uint8_t pk[PUBLICKEY_BYTES],
                const uint8_t mu[DELTA_BYTES],
                const uint8_t seed[DELTA_BYTES]) {

    uint8_t seed_r[DELTA_BYTES] = {0};
    public_key pk_tmp;
    load_from_string_pk(&pk_tmp, pk);

    // Compute a vector r = hwt(delta, H'(pk))
    polyvec r;
    nttpolyvec rhat[2] = {0};
    memset(&r, 0, sizeof(polyvec));

    if (seed == NULL)
        randombytes(seed_r, DELTA_BYTES);
    else
        cmov(seed_r, seed, DELTA_BYTES, 1);
    genRx_vec(&r, seed_r);

    // Compute c1(x), c2(x)
    ciphertext ctxt_tmp;
    memset(&ctxt_tmp, 0, sizeof(ciphertext));
    computeC1(&(ctxt_tmp.c1), rhat, pk_tmp.A, &r);
    computeC2(&(ctxt_tmp.c2), mu, &pk_tmp.b, rhat);

    save_to_string(ctxt, &ctxt_tmp);
}

/*************************************************
 * Name:        indcpa_dec
 *
 * Description: Decryption function of the CPA-secure
 *              Module-Lizard public-key encryption scheme.
 *
 * Arguments:   - uint8_t *delta: pointer to output decrypted delta
 *                (of length DELTA_BYTES), assumed to be already initialized
 *              - secret_key *sk: pointer to input private key
 *                (a structure composed of (vector s, t, vector negstart)
 *              - ciphertext *ctxt: pointer to input ciphertext
 *                (a structure composed of (vector c1, c2))
 **************************************************/
void indcpa_dec(uint8_t delta[DELTA_BYTES],
                const uint8_t sk[PKE_SECRETKEY_BYTES],
                const uint8_t ctxt[CIPHERTEXT_BYTES]) {
    poly delta_temp;
    polyvec c1_temp;

    secret_key sk_tmp;
    memset(&sk_tmp, 0, sizeof(secret_key));
    load_from_string_sk(&sk_tmp, sk);

    ciphertext ctxt_tmp;
    load_from_string(&ctxt_tmp, ctxt);

    unsigned int i, j;
    c1_temp = ctxt_tmp.c1;
    delta_temp = ctxt_tmp.c2;
    for (i = 0; i < LWE_N; ++i)
        delta_temp.coeffs[i] <<= _16_LOG_P2;
    for (i = 0; i < MODULE_RANK; ++i)
        for (j = 0; j < LWE_N; ++j)
            c1_temp.vec[i].coeffs[j] <<= _16_LOG_P;

    // Compute delta = (delta + c1^T * s)
    vec_vec_mult_add_p(&delta_temp, &c1_temp, &sk_tmp);

    // Compute delta = 2/p * delta
    for (i = 0; i < LWE_N; ++i) {
        delta_temp.coeffs[i] += DEC_ADD;
        delta_temp.coeffs[i] >>= _16_LOG_T;
        delta_temp.coeffs[i] &= 0x01;
    }

    // Set delta
    memset(delta, 0, DELTA_BYTES);
    for (i = 0; i < DELTA_BYTES; ++i) {
        for (j = 0; j < 8; ++j) {
            delta[i] ^= ((uint8_t)(delta_temp.coeffs[8 * i + j]) << j);
        }
    }
}
