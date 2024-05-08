#ifndef API_H
#define API_H

#include "params.h"

#define CRYPTO_SECRETKEYBYTES  HAETAE_CRYPTO_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES  HAETAE_CRYPTO_PUBLICKEYBYTES
#define CRYPTO_BYTES           HAETAE_CRYPTO_BYTES

#define CRYPTO_ALGNAME "HAETAE2"

int crypto_sign_keypair(unsigned char *pk, unsigned char  *sk);


int crypto_sign(unsigned char  *sig, size_t *siglen, const unsigned char  *m,
                          size_t mlen, const unsigned char  *sk);

int crypto_sign_open(unsigned char  *m, size_t *mlen, const unsigned char  *sm, size_t smlen,
                     const unsigned char  *pk);

#endif
