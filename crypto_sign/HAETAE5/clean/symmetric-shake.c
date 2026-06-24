// SPDX-License-Identifier: MIT

#include "fips202.h"
#include "params.h"
#include "symmetric.h"

#include <stdint.h>

void haetae_shake256_absorb_once(xof256_state *state, const uint8_t *in,
                                 size_t inlen) {
  shake256_inc_init(state);
  shake256_inc_absorb(state, in, inlen);
  shake256_inc_finalize(state);
}

void haetae_shake256_absorb_twice(xof256_state *state, const uint8_t *in1,
                                  size_t in1len, const uint8_t *in2,
                                  size_t in2len) {
  shake256_inc_init(state);
  shake256_inc_absorb(state, in1, in1len);
  shake256_inc_absorb(state, in2, in2len);
  shake256_inc_finalize(state);
}

void haetae_shake256_absorb_thrice(xof256_state *state, const uint8_t *in1,
                                   size_t in1len, const uint8_t *in2,
                                   size_t in2len, const uint8_t *in3,
                                   size_t in3len) {
  shake256_inc_init(state);
  shake256_inc_absorb(state, in1, in1len);
  shake256_inc_absorb(state, in2, in2len);
  shake256_inc_absorb(state, in3, in3len);
  shake256_inc_finalize(state);
}

void haetae_shake256_squeezeblocks(uint8_t *output, size_t nblocks,
                                   xof256_state *state) {
  shake256_inc_squeeze(output, nblocks * SHAKE256_RATE, state);
}

void haetae_shake128_stream_init(stream128_state *state,
                                 const uint8_t seed[HAETAE_SEEDBYTES],
                                 uint16_t nonce) {
  uint8_t t[2];
  t[0] = nonce;
  t[1] = nonce >> 8;

  shake128_inc_init(state);
  shake128_inc_absorb(state, seed, HAETAE_SEEDBYTES);
  shake128_inc_absorb(state, t, 2);
  shake128_inc_finalize(state);
}

void haetae_shake256_stream_init(stream256_state *state,
                                 const uint8_t seed[HAETAE_CRHBYTES],
                                 uint16_t nonce) {
  uint8_t t[2];
  t[0] = nonce;
  t[1] = nonce >> 8;

  shake256_inc_init(state);
  shake256_inc_absorb(state, seed, HAETAE_CRHBYTES);
  shake256_inc_absorb(state, t, 2);
  shake256_inc_finalize(state);
}

void haetae_shake128_stream_squeezeblocks(uint8_t *output, size_t nblocks,
                                          stream128_state *state) {
  shake128_inc_squeeze(output, nblocks * SHAKE128_RATE, state);
}

void haetae_shake256_stream_squeezeblocks(uint8_t *output, size_t nblocks,
                                          stream256_state *state) {
  shake256_inc_squeeze(output, nblocks * SHAKE256_RATE, state);
}
