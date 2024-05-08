#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "randombytes.h"
#include "cpucycles.h"
#include "api.h"
#include "mqs_config.h"

#include <time.h>

#define TEST_LOOP 1000
#define MLEN 24
// MQSign mode -> mqs_config.h

int PQC_bench(void)
{
#if defined(__aarch64__)
    setup_rdtsc();
#endif

    unsigned char* pk = (unsigned char*)malloc(CRYPTO_PUBLICKEYBYTES+MLEN);
    unsigned char* sk = (unsigned char*)malloc(CRYPTO_SECRETKEYBYTES+MLEN);

//    unsigned char  m[100] = "kpqc benchmark system";
    unsigned char  m[100+MLEN];

    unsigned char sm[CRYPTO_BYTES + 200];

    unsigned char  m2[100];

    unsigned long long mlen = 0;
    unsigned long long smlen = 0;

    unsigned long long m2len;

    int result;

    unsigned long long kcycles;
    unsigned long long cycles1, cycles2;

    randombytes(m, MLEN);
    mlen = MLEN;
    
    printf("BENCHMARK ENVIRONMENTS  ============================= \n");
    printf("CRYPTO_ALGNAME: %s\n", CRYPTO_ALGNAME);
    printf("CRYPTO_PUBLICKEYBYTES: %d\n", CRYPTO_PUBLICKEYBYTES);
    printf("CRYPTO_SECRETKEYBYTES: %d\n", CRYPTO_SECRETKEYBYTES);
    printf("CRYPTO_BYTES: %d\n", CRYPTO_BYTES);
    printf("Number of loop: %d \n", TEST_LOOP);
//     printf("KeyGen ////////////////////////////////////////////// \n");
    
//     kcycles=0;
    unsigned char sk_seed[LEN_SKSEED] = { 0 };
    unsigned char salt_source[_SALT_SOURCE_LEN] = { 0 };
    randombytes(sk_seed, LEN_SKSEED);
    randombytes(salt_source, _SALT_SOURCE_LEN);
    
    for (int i = 0; i < TEST_LOOP; i++)
    {
    cycles1 = cpucycles();
    crypto_sign_keypair(pk, sk, sk_seed);
    cycles2 = cpucycles();
        kcycles += cycles2-cycles1;
    }
    printf("  KeyGen runs in ................. %8lld nsec", kcycles/TEST_LOOP);
    printf("\n");

    printf("Sign //////////////////////////////////////////////// \n");
    kcycles=0;
    for (int i = 0; i < TEST_LOOP; i++)
    {
        cycles1 = cpucycles();
        crypto_sign(sm, &smlen, m, mlen, sk, sk_seed, salt_source);
        cycles2 = cpucycles();
        kcycles += cycles2-cycles1;
    }
    printf("  Sign runs in ................. %8lld nsec", kcycles / TEST_LOOP);
    printf("\n");
 

    printf("Verify ////////////////////////////////////////////// \n");
    kcycles = 0;
    for (int i = 0; i < TEST_LOOP; i++)
    {
        cycles1 = cpucycles();
        result = crypto_sign_open(m2, &m2len, sm, smlen, pk);
        cycles2 = cpucycles();
        kcycles += cycles2 - cycles1;
    }
    printf("  Verify runs in ................. %8lld nsec", kcycles / TEST_LOOP);
    printf("\n");

    
    printf("==================================================== \n");

    return 0;
}

int main()
{
    PQC_bench();
}
