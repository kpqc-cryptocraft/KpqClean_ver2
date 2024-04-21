#include <stdio.h>
#include <string.h>

#include "api.h"
#include "cpucycles.h"
#include "randombytes.h"

#define TEST_LOOP 1000
#define MLEN 24

int PQC_bench(void)
{
#if defined(__aarch64__)
    setup_rdtsc();
#endif

    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char sk[CRYPTO_SECRETKEYBYTES];
    unsigned char m[MLEN + CRYPTO_BYTES];
    unsigned char m2[MLEN + CRYPTO_BYTES];
    unsigned char sm[MLEN + CRYPTO_BYTES];

    unsigned long long mlen;
    unsigned long long smlen;

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
    printf("KeyGen ////////////////////////////////////////////// \n");
    
    kcycles=0;
    for (int i = 0; i < TEST_LOOP; i++)
    {
        cycles1 = cpucycles();
        crypto_sign_keypair(pk, sk);
        cycles2 = cpucycles();
        kcycles += cycles2-cycles1;
    }
    printf("  KeyGen runs in ................. %8lld cycles", kcycles/TEST_LOOP);
    printf("\n");


    printf("Sign //////////////////////////////////////////////// \n");
    kcycles=0;
    for (int i = 0; i < TEST_LOOP; i++)
    {
        cycles1 = cpucycles();
        crypto_sign(sm, &smlen, m, mlen, sk);
        cycles2 = cpucycles();
        kcycles += cycles2-cycles1;
    }
    printf("  Sign runs in ................. %8lld cycles", kcycles / TEST_LOOP);
    printf("\n");

    printf("Verify ////////////////////////////////////////////// \n");
    kcycles = 0;
    for (int i = 0; i < TEST_LOOP; i++)
    {
        cycles1 = cpucycles();
        result = crypto_sign_open(m2, &mlen, sm, smlen, pk);
        cycles2 = cpucycles();
        kcycles += cycles2 - cycles1;
    }
    
    printf("  Verify runs in ................. %8lld cycles", kcycles / TEST_LOOP);
    printf("\n");
    
    printf("==================================================== \n");

    return 0;
}

int main()
{
    PQC_bench();
}
