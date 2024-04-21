#ifndef KEM_TIMER_H
#define KEM_TIMER_H

#include <stdint.h>
#include <stdio.h>
#include "parameters.h"

#define CRYPTO_SECRETKEYBYTES  timer_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES  timer_PUBLICKEYBYTES
#define CRYPTO_CIPHERTEXTBYTES timer_CIPHERTEXTBYTES
#define CRYPTO_BYTES           timer_BYTES

#define CRYPTO_ALGNAME "SMAUG-Timer"

#define crypto_kem_keypair timer_crypto_kem_keypair
#define crypto_kem_enc  timer_crypto_kem_encap
#define crypto_kem_dec timer_crypto_kem_decap

#define timer_SECRETKEYBYTES KEM_SECRETKEY_BYTES
#define timer_PUBLICKEYBYTES PUBLICKEY_BYTES
#define timer_CIPHERTEXTBYTES CIPHERTEXT_BYTES
#define timer_BYTES 32

int timer_crypto_kem_keypair(uint8_t *pk, uint8_t *sk);
int timer_crypto_kem_encap(uint8_t *ct, uint8_t *ss, const uint8_t *pk);
int timer_crypto_kem_decap(uint8_t *ss, const uint8_t *sk, const uint8_t *pk,
                           const uint8_t *ctxt);
#endif // KEM_TIMER_H
