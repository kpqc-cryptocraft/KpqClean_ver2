#ifndef KEM_SMAUG_H
#define KEM_SMAUG_H

#include <stdint.h>
#include <stdio.h>

#define CRYPTO_SECRETKEYBYTES  cryptolab_smaug5_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES  cryptolab_smaug5_PUBLICKEYBYTES
#define CRYPTO_CIPHERTEXTBYTES cryptolab_smaug5_CIPHERTEXTBYTES
#define CRYPTO_BYTES           cryptolab_smaug5_BYTES

#define CRYPTO_ALGNAME "SMAUG-T5"

#define crypto_kem_keypair cryptolab_smaug5_crypto_kem_keypair
#define crypto_kem_enc  cryptolab_smaug5_crypto_kem_enc
#define crypto_kem_dec cryptolab_smaug5_crypto_kem_dec

#define cryptolab_smaug5_SECRETKEYBYTES 160 + 672
#define cryptolab_smaug5_PUBLICKEYBYTES 672
#define cryptolab_smaug5_CIPHERTEXTBYTES 672
#define cryptolab_smaug5_BYTES 32


int cryptolab_smaug1_crypto_kem_keypair(uint8_t *pk, uint8_t *sk);
int cryptolab_smaug1_crypto_kem_enc(uint8_t *ct, uint8_t *ss,
                                    const uint8_t *pk);
int cryptolab_smaug1_crypto_kem_dec(uint8_t *ss, const uint8_t *ctxt,
                                    const uint8_t *sk);

#define cryptolab_smaug3_SECRETKEYBYTES 224 + 1088
#define cryptolab_smaug3_PUBLICKEYBYTES 1088
#define cryptolab_smaug3_CIPHERTEXTBYTES 992
#define cryptolab_smaug3_BYTES 32

int cryptolab_smaug3_crypto_kem_keypair(uint8_t *pk, uint8_t *sk);
int cryptolab_smaug3_crypto_kem_enc(uint8_t *ct, uint8_t *ss,
                                    const uint8_t *pk);
int cryptolab_smaug3_crypto_kem_dec(uint8_t *ss, const uint8_t *ctxt,
                                    const uint8_t *sk);

#define cryptolab_smaug5_SECRETKEYBYTES 352 + 1440
#define cryptolab_smaug5_PUBLICKEYBYTES 1440
#define cryptolab_smaug5_CIPHERTEXTBYTES 1376
#define cryptolab_smaug5_BYTES 32

int cryptolab_smaug5_crypto_kem_keypair(uint8_t *pk, uint8_t *sk);
int cryptolab_smaug5_crypto_kem_enc(uint8_t *ct, uint8_t *ss,
                                    const uint8_t *pk);
int cryptolab_smaug5_crypto_kem_dec(uint8_t *ss, const uint8_t *ctxt,
                                    const uint8_t *sk);
#endif // KEM_SMAUG_H
