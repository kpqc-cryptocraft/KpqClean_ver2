#include "keccakx4_vec.h"
#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static void keccakx4_squeezeblocks_vec(__m256i *out,
                                   size_t nblocks,
                                   unsigned int r,
                                   __m256i s[25])
{
  unsigned int i;

  while(nblocks > 0) {
    f1600x4(s, KeccakF_RoundConstants);
    for(i=0; i < r/8; ++i) {
      out[i] = s[i];
    }

    out += r/8;
    --nblocks;
  }
}


void shake256x4_squeezeblocks_vec(__m256i *buf,
                              size_t nblocks,
                              keccakx4_state *state)
{
  keccakx4_squeezeblocks_vec(buf, nblocks, SHAKE256_RATE, state->s);
}
