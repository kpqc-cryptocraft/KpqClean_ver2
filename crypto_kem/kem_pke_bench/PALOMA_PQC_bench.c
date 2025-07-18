#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "api.h"
#include "cpucycles.h"

#define TEST_LOOP 1

uint64_t t[TEST_LOOP];

int PQC_bench(void)
{
#if defined(__aarch64__)
    setup_rdtsc();
#endif
    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char sk[CRYPTO_SECRETKEYBYTES];
    unsigned char ct[CRYPTO_CIPHERTEXTBYTES];
    unsigned char ss[CRYPTO_BYTES];
    unsigned char dss[CRYPTO_BYTES];

    unsigned long long kcycles;
    unsigned long long cycles1, cycles2;

    printf("BENCHMARK ENVIRONMENTS  ============================= \n");
    printf("CRYPTO_ALGNAME: %s\n", CRYPTO_ALGNAME);
    printf("CRYPTO_PUBLICKEYBYTES: %d\n", CRYPTO_PUBLICKEYBYTES);
    printf("CRYPTO_SECRETKEYBYTES: %d\n", CRYPTO_SECRETKEYBYTES);
    printf("CRYPTO_BYTES: %d\n", CRYPTO_BYTES);
    printf("CRYPTO_CIPHERTEXTBYTES: %d\n", CRYPTO_CIPHERTEXTBYTES);
    printf("Number of loop: %d \n", TEST_LOOP);
    printf("KeyGen ////////////////////////////////////////////// \n");
    
    /* Step 1: Generate Precomputation Table */
    gf2m_tab gf2m_tables;
    gen_precomputation_tab(&gf2m_tables);

    kcycles=0;
    for (int i = 0; i < TEST_LOOP; i++)
    {
        cycles1 = cpucycles();
        crypto_kem_keypair(pk, sk, &gf2m_tables);
        cycles2 = cpucycles();
        kcycles += cycles2-cycles1;
    }
    printf("  KeyGen runs in .................  %8lld cycles", kcycles/TEST_LOOP);
    printf("\n");

    printf("Encapsulation /////////////////////////////////////// \n");
    kcycles=0;
    for (int i = 0; i < TEST_LOOP; i++)
    {
        cycles1 = cpucycles();
        crypto_kem_enc(ct, ss, pk);
        cycles2 = cpucycles();
        kcycles += cycles2-cycles1;

    }

    printf("  Encapsulation  runs in .........  %8lld cycles", kcycles/TEST_LOOP);
    printf("\n");

    printf("Decapsulation /////////////////////////////////////// \n");
    kcycles=0;
    for (int i = 0; i < TEST_LOOP; i++)
    {
        cycles1 = cpucycles();
        crypto_kem_dec(dss, ct, sk, &gf2m_tables);
        cycles2 = cpucycles();
        kcycles += cycles2-cycles1;
    }
    
    printf("  Decapsulation  runs in .........  %8lld cycles", kcycles/TEST_LOOP);
    printf("\n");

    printf("==================================================== \n");

    return 0;
}

int main()
{
    PQC_bench();
}
