#ifndef API_H
#define API_H
#include "params.h"

#include "config.h"

#define CRYPTO_PUBLICKEYBYTES NCC_CRYPTO_PUBLICKEYBYTES
#define CRYPTO_SECRETKEYBYTES NCC_CRYPTO_SECRETKEYBYTES
#define CRYPTO_BYTES NCC_CRYPTO_BYTES

#define CRYPTO_ALGNAME "NCC-Sign5"

int crypto_sign_keypair(unsigned char *pk, unsigned char *sk);

int crypto_sign_signature(unsigned char *sm, unsigned long long *smlen,
                const unsigned char *msg, unsigned long long len,
                const unsigned char *sk);

int crypto_sign(unsigned char *sm, size_t *smlen,
                const unsigned char *m, size_t mlen,
                const unsigned char *sk);

int crypto_sign_open(unsigned char *m, unsigned long long *mlen,
                     const unsigned char *sm, unsigned long long smlen,
                     const unsigned char *pk);

#endif
