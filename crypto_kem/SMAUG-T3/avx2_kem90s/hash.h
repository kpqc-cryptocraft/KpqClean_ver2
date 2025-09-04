#ifndef SMAUG_HASH_H
#define SMAUG_HASH_H

#include "../common/Keccak_avx2/fips202.h"
#include "parameters.h"

#include "aes256ctr.h"

#include "sha2.h"

#define SHA_256_HashSize 32
#define SHA_512_HashSize 64

// #define hash_h(OUT, IN, INBYTES) sha256(OUT, IN, INBYTES)
// #define hash_g(OUT, OUTBYTES, IN1, IN1BYTES, IN2, IN2BYTES)                    \
//     shake256_absorb_twice_squeeze(OUT, OUTBYTES, IN1, IN1BYTES, IN2, IN2BYTES)

#define sha512_absorb_twice SMAUG_NAMESPACE(sha512_absorb_twice)
void sha512_absorb_twice(uint8_t *out, size_t out_bytes, const uint8_t *in1,
                         size_t in1_bytes, const uint8_t *in2,
                         size_t in2_bytes);

#define hash_h(OUT, IN, INBYTES) sha256(OUT, IN, INBYTES)
#define hash_g(OUT, OUTBYTES, IN1, IN1BYTES, IN2, IN2BYTES)                    \
    sha512_absorb_twice(OUT, OUTBYTES, IN1, IN1BYTES, IN2, IN2BYTES)


// #define shake256_absorb_twice_squeeze                                          \
//     SMAUG_NAMESPACE(shake256_absorb_twice_squeeze)
// void shake256_absorb_twice_squeeze(uint8_t *out, size_t out_bytes,
//                                    const uint8_t *in1, size_t in1_bytes,
//                                    const uint8_t *in2, size_t in2_bytes);

#define XOF_MAXBLOCK                                                           \
    ((PKPOLYMAT_BYTES + (AES256CTR_BLOCKBYTES - 1)) / AES256CTR_BLOCKBYTES)
#define HASH_G_INBYTES (T_BYTES + SHA_256_HashSize)

#define aes256ctr_xof SMAUG_NAMESPACE(aes256ctr_xof)
void aes256ctr_xof(uint8_t *output, size_t out_bytes, const uint8_t *input,
                   size_t in_bytes);

#endif // SMAUG_HASH_H
