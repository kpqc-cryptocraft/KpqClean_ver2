#ifndef KEM_TIMER_H
#define KEM_TIMER_H

#include <stdint.h>
#include <stdio.h>
#include "parameters.h"

#define CRYPTO_SECRETKEYBYTES  cryptolab_smaug5_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES  cryptolab_smaug5_PUBLICKEYBYTES
#define CRYPTO_CIPHERTEXTBYTES cryptolab_smaug5_CIPHERTEXTBYTES
#define CRYPTO_BYTES           cryptolab_smaug5_BYTES

#define CRYPTO_ALGNAME "SMAUG-TIMER"

// SMAUG_NAMESPACE 사용 (parameters.h에서 정의됨)
#define crypto_kem_keypair SMAUG_NAMESPACE(crypto_kem_keypair)
#define crypto_kem_enc SMAUG_NAMESPACE(crypto_kem_enc)
#define crypto_kem_dec SMAUG_NAMESPACE(crypto_kem_dec)
 
#define cryptolab_smaug5_SECRETKEYBYTES 160 + 672
#define cryptolab_smaug5_PUBLICKEYBYTES 672
#define cryptolab_smaug5_CIPHERTEXTBYTES 608
#define cryptolab_smaug5_BYTES 32

int crypto_kem_keypair(uint8_t *pk, uint8_t *sk);
int crypto_kem_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk);
int crypto_kem_dec(uint8_t *ss, const uint8_t *sk, const uint8_t *pk);

#endif // KEM_TIMER_H