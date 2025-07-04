#ifndef KEM_SMAUG_H
#define KEM_SMAUG_H

#include <stdint.h>
#include <stdio.h>

#include "parameters.h"


#define CRYPTO_SECRETKEYBYTES  cryptolab_smaug5_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES  cryptolab_smaug5_PUBLICKEYBYTES
#define CRYPTO_CIPHERTEXTBYTES cryptolab_smaug5_CIPHERTEXTBYTES
#define CRYPTO_BYTES           cryptolab_smaug5_BYTES


#define CRYPTO_ALGNAME "SMAUG-T5"

// // 네임스페이스 적용
#define crypto_kem_keypair SMAUG_NAMESPACE(crypto_kem_keypair)
#define crypto_kem_enc SMAUG_NAMESPACE(crypto_kem_enc)
#define crypto_kem_dec SMAUG_NAMESPACE(crypto_kem_dec)

#define cryptolab_smaug5_SECRETKEYBYTES 352 + 1440
#define cryptolab_smaug5_PUBLICKEYBYTES 1440
#define cryptolab_smaug5_CIPHERTEXTBYTES 1376
#define cryptolab_smaug5_BYTES 32


int crypto_kem_keypair(uint8_t *pk, uint8_t *sk);
int crypto_kem_enc(uint8_t *ct, uint8_t *ss,
                                      const uint8_t *pk);
int crypto_kem_dec(uint8_t *ss, const uint8_t *sk,
                                      const uint8_t *pk);
#endif // KEM_SMAUG_H
