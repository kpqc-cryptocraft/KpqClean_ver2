// SPDX-License-Identifier: MIT

#ifndef SMAUGT_API_H
#define SMAUGT_API_H

#include "params.h"

#include <stdint.h>

/* Export API in SUPERCOP naming scheme CRYPTO_xxx / crypto_kem_xxx */
#define CRYPTO_SECRETKEYBYTES SMAUGT_KEM_SECRETKEY_BYTES
#define CRYPTO_PUBLICKEYBYTES SMAUGT_PUBLICKEY_BYTES
#define CRYPTO_CIPHERTEXTBYTES SMAUGT_CIPHERTEXT_BYTES
#define CRYPTO_BYTES SMAUGT_SHARED_SECRETE_BYTES
#define CRYPTO_ALGNAME SMAUGT_CRYPTO_ALGNAME

#define crypto_kem_keypair_internal SMAUGT_NAMESPACE(keypair_internal)
#define crypto_kem_keypair SMAUGT_NAMESPACE(keypair)
#define crypto_kem_enc_internal SMAUGT_NAMESPACE(enc_internal)
#define crypto_kem_enc SMAUGT_NAMESPACE(enc)
#define crypto_kem_dec_internal SMAUGT_NAMESPACE(dec_internal)
#define crypto_kem_dec SMAUGT_NAMESPACE(dec)

int crypto_kem_keypair_internal(uint8_t *pk, uint8_t *sk,
                                uint8_t d[SMAUGT_T_BYTES],
                                uint8_t seed[SMAUGT_CRYPTO_BYTES]);
int crypto_kem_keypair(uint8_t *pk, uint8_t *sk);

int crypto_kem_enc_internal(uint8_t *ctxt, uint8_t *ss, const uint8_t *pk,
                            const uint8_t *mu);
int crypto_kem_enc(uint8_t *ctxt, uint8_t *ss, const uint8_t *pk);

int crypto_kem_dec_internal(uint8_t *ss, const uint8_t *ctxt,
                            const uint8_t *sk);
int crypto_kem_dec(uint8_t *ss, const uint8_t *ctxt, const uint8_t *sk);

#endif /* !SMAUGT_API_H */
