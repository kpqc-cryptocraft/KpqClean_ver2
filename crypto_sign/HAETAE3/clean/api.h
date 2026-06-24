// SPDX-License-Identifier: MIT

#ifndef HAETAE_API_H
#define HAETAE_API_H

#include "params.h"

#include <stddef.h>
#include <stdint.h>

#define CRYPTO_ALGNAME HAETAE_CRYPTO_ALGNAME
#define CRYPTO_SECRETKEYBYTES HAETAE_CRYPTO_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES HAETAE_CRYPTO_PUBLICKEYBYTES
#define CRYPTO_BYTES HAETAE_CRYPTO_BYTES

#define crypto_sign_keypair HAETAE_NAMESPACE(keypair)
int crypto_sign_keypair(uint8_t *vk, uint8_t *sk);

#define crypto_sign_keypair_internal HAETAE_NAMESPACE(keypair_internal)
int crypto_sign_keypair_internal(uint8_t *vk, uint8_t *sk,
                                 uint8_t seed[HAETAE_SEEDBYTES]);

#define crypto_sign_signature_internal HAETAE_NAMESPACE(signature_internal)
int crypto_sign_signature_internal(uint8_t *sig, size_t *siglen,
                                   const uint8_t *m, size_t mlen,
                                   const uint8_t *pre, size_t prelen,
                                   const uint8_t rnd[HAETAE_SEEDBYTES],
                                   const uint8_t *sk);

#define crypto_sign_signature HAETAE_NAMESPACE(signature)
int crypto_sign_signature(uint8_t *sig, size_t *siglen, const uint8_t *m,
                          size_t mlen, const uint8_t *ctx, size_t ctxlen,
                          const uint8_t *sk);

/* HAETAE 1.1.2 7-arg crypto_sign */
int crypto_sign(uint8_t *sm, size_t *smlen, const uint8_t *m, size_t mlen,
                const uint8_t *ctx, size_t ctxlen, const uint8_t *sk);

#define crypto_sign_verify_internal HAETAE_NAMESPACE(verify_internal)
int crypto_sign_verify_internal(const uint8_t *sig, size_t siglen,
                                const uint8_t *m, size_t mlen,
                                const uint8_t *pre, size_t prelen,
                                const uint8_t *vk);

#define crypto_sign_verify HAETAE_NAMESPACE(verify)
int crypto_sign_verify(const uint8_t *sig, size_t siglen, const uint8_t *m,
                       size_t mlen, const uint8_t *ctx, size_t ctxlen,
                       const uint8_t *vk);

/* HAETAE 1.1.2 7-arg crypto_sign_open */
int crypto_sign_open(uint8_t *m, size_t *mlen, const uint8_t *sm, size_t smlen,
                     const uint8_t *ctx, size_t ctxlen, const uint8_t *vk);

/* NIST 5-arg shims for KpqClean PQCgenKAT_sign.c (ctx=NULL, ctxlen=0).
 * Macro self-reference is expanded only once per C99 rules, so the inner
 * crypto_sign(...) is the real 7-arg function call. */
#define crypto_sign(sm, smlen, m, mlen, sk)                                    \
  crypto_sign((sm), (smlen), (m), (mlen), NULL, 0, (sk))
#define crypto_sign_open(m, mlen, sm, smlen, pk)                               \
  crypto_sign_open((m), (mlen), (sm), (smlen), NULL, 0, (pk))

#endif // HAETAE_API_H
