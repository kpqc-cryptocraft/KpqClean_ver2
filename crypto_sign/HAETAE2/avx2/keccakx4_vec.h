#ifndef FIPS202X4_H_VEC
#define FIPS202X4_H_VEC
#ifdef __ASSEMBLER__
/* The C ABI on MacOS exports all symbols with a leading
 * underscore. This means that any symbols we refer to from
 * C files (functions) can't be found, and all symbols we
 * refer to from ASM also can't be found.
 *
 * This define helps us get around this
 */
#if defined(__WIN32__) || defined(__APPLE__)
#define decorate(s) _##s
#define _cdecl(s) decorate(s)
#define cdecl(s) ##s
#else

#define _cdecl(s) _##s
#define cdecl(s) s
#endif

#else
#include <stddef.h>
#include <stdint.h>
#include <immintrin.h>
#include "keccak4x/fips202x4.h"
#include "Keccak_avx2/fips202.h"

#define NROUNDS 24

static const uint64_t KeccakF_RoundConstants[NROUNDS] = {
    0x0000000000000001ULL, 0x0000000000008082ULL,
    0x800000000000808aULL, 0x8000000080008000ULL,
    0x000000000000808bULL, 0x0000000080000001ULL,
    0x8000000080008081ULL, 0x8000000000008009ULL,
    0x000000000000008aULL, 0x0000000000000088ULL,
    0x0000000080008009ULL, 0x000000008000000aULL,
    0x000000008000808bULL, 0x800000000000008bULL,
    0x8000000000008089ULL, 0x8000000000008003ULL,
    0x8000000000008002ULL, 0x8000000000000080ULL,
    0x000000000000800aULL, 0x800000008000000aULL,
    0x8000000080008081ULL, 0x8000000000008080ULL,
    0x0000000080000001ULL, 0x8000000080008008ULL
};

extern void f1600x4(__m256i *s, const uint64_t *rc);

void shake256x4_squeezeblocks_vec(__m256i *buf,
                              size_t nblocks,
                              keccakx4_state *state);
#endif
#endif