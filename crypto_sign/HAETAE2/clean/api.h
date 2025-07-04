#ifndef API_H
#define API_H

#include "params.h"

#define CRYPTO_SECRETKEYBYTES  HAETAE_CRYPTO_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES  HAETAE_CRYPTO_PUBLICKEYBYTES
#define CRYPTO_BYTES           HAETAE_CRYPTO_BYTES

#define CRYPTO_ALGNAME "HAETAE2"

int crypto_sign_keypair(uint8_t *pk, uint8_t *sk);


int crypto_sign(uint8_t *sig, size_t *siglen, const uint8_t *m,
                          size_t mlen, const uint8_t *sk);

int crypto_sign_open(uint8_t *m, size_t *mlen, const uint8_t *sm, size_t smlen,
                     const uint8_t *pk);

#endif
