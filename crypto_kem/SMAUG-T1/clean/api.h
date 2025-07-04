#ifndef KEM_SMAUG_H
#define KEM_SMAUG_H

#include <stdint.h>
#include <stdio.h>
#include "parameters.h"

#define CRYPTO_SECRETKEYBYTES  cryptolab_smaug1_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES  cryptolab_smaug1_PUBLICKEYBYTES
#define CRYPTO_CIPHERTEXTBYTES cryptolab_smaug1_CIPHERTEXTBYTES
#define CRYPTO_BYTES           cryptolab_smaug1_BYTES


#define CRYPTO_ALGNAME "SMAUG-T1"

// 네임스페이스 적용
#define crypto_kem_keypair SMAUG_NAMESPACE(crypto_kem_keypair)
#define crypto_kem_enc SMAUG_NAMESPACE(crypto_kem_enc)
#define crypto_kem_dec SMAUG_NAMESPACE(crypto_kem_dec)

#define cryptolab_smaug1_SECRETKEYBYTES 160 + 672
#define cryptolab_smaug1_PUBLICKEYBYTES 672
#define cryptolab_smaug1_CIPHERTEXTBYTES 672
#define cryptolab_smaug1_BYTES 32

//#define crypto_kem_keypair SMAUG_NAMESPACE(crypto_kem_keypair)
int crypto_kem_keypair(uint8_t *pk, uint8_t *sk);
//#define crypto_kem_enc SMAUG_NAMESPACE(crypto_kem_enc)
int crypto_kem_enc(uint8_t *ss, uint8_t *ctxt, const uint8_t *pk);
//#define crypto_kem_dec SMAUG_NAMESPACE(crypto_kem_dec)
int crypto_kem_dec(uint8_t *ss, const uint8_t *ctxt, const uint8_t *sk);


#endif // KEM_SMAUG_H