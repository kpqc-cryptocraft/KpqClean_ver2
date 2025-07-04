#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "api.h"
#include "../../common/cpucycles.h"

#define TEST_LOOP 10000

static int PQC_bench(void)
{

#if defined(__aarch64__)
    setup_rdtsc();
#endif

    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
	unsigned char sk[CRYPTO_SECRETKEYBYTES];
	unsigned char ct[CRYPTO_CIPHERTEXTBYTES];
	unsigned char m[CRYPTO_MAXPLAINTEXT] = {0};
	unsigned char dm[CRYPTO_MAXPLAINTEXT];
	unsigned long long mlen = 0;
	unsigned long long dmlen = 0;
	unsigned long long clen = 0;

    unsigned long long kcycles, ecycles, dcycles;
    unsigned long long cycles1, cycles2;

    printf("BENCHMARK ENVIRONMENTS  ============================= \n");
    printf("CRYPTO_ALGNAME: %s\n", CRYPTO_ALGNAME);
    printf("CRYPTO_PUBLICKEYBYTES: %d\n", CRYPTO_PUBLICKEYBYTES);
    printf("CRYPTO_SECRETKEYBYTES: %d\n", CRYPTO_SECRETKEYBYTES);
    printf("CRYPTO_BYTES: %d\n", CRYPTO_BYTES);
    printf("CRYPTO_CIPHERTEXTBYTES: %d\n", CRYPTO_CIPHERTEXTBYTES);
    printf("Number of loop: %d \n", TEST_LOOP);
    printf("KeyGen ////////////////////////////////////////////// \n");

    kcycles=0;
    for (int i = 0; i < TEST_LOOP; i++)
    {
        cycles1 = cpucycles();
        crypto_encrypt_keypair(pk, sk);
        cycles2 = cpucycles();
        kcycles += cycles2-cycles1;
    }
    printf("  KeyGen runs in ................. %8lld cycles", kcycles/TEST_LOOP);
    printf("\n");

    ecycles=0;
	dcycles=0;

	mlen = 32;

	for (int i = 0; i < TEST_LOOP; i++)
	{
		cycles1 = cpucycles();
		crypto_encrypt(ct, &clen, m, mlen, pk);
        cycles2 = cpucycles();
        ecycles += cycles2-cycles1;

		cycles1 = cpucycles(); 
		crypto_encrypt_open(dm, &dmlen, ct, clen, sk);
		cycles2 = cpucycles();
        dcycles += cycles2-cycles1;
	}

    printf("Encrypt /////////////////////////////////////// \n");
    printf("  ENC    runs in ................. %8lld cycles", ecycles/TEST_LOOP);
    printf("\n"); 

    printf("Encrypt Open /////////////////////////////////////// \n");
    printf("  DEC    runs in ................. %8lld cycles", dcycles/TEST_LOOP);
    printf("\n"); 

    printf("==================================================== \n");

    return 0;
}

int main(void)
{
    PQC_bench();
}
