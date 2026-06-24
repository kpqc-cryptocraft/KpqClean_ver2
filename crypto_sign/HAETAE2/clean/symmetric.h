// SPDX-License-Identifier: MIT

#ifndef HAETAE_SYMMETRIC_H
#define HAETAE_SYMMETRIC_H

#include "fips202.h"
#include "params.h"

#include <stdint.h>

// Cryptographic XOF: shake256 (incremental, common/fips202.c)
typedef shake256incctx xof256_state;

void haetae_shake256_absorb_once(xof256_state *state, const uint8_t *in,
                                 size_t inlen);
void haetae_shake256_absorb_twice(xof256_state *state, const uint8_t *in1,
                                  size_t in1len, const uint8_t *in2,
                                  size_t in2len);
void haetae_shake256_absorb_thrice(xof256_state *state, const uint8_t *in1,
                                   size_t in1len, const uint8_t *in2,
                                   size_t in2len, const uint8_t *in3,
                                   size_t in3len);
void haetae_shake256_squeezeblocks(uint8_t *output, size_t nblocks,
                                   xof256_state *state);

#define XOF256_BLOCKBYTES SHAKE256_RATE

#define xof256_absorb_once(STATE, IN, IN_LEN)                                  \
  haetae_shake256_absorb_once(STATE, IN, IN_LEN)
#define xof256_absorb_twice(STATE, IN, IN_LEN, IN2, IN2_LEN)                   \
  haetae_shake256_absorb_twice(STATE, IN, IN_LEN, IN2, IN2_LEN)
#define xof256_absorb_thrice(STATE, IN, IN_LEN, IN2, IN2_LEN, IN3, IN3_LEN)    \
  haetae_shake256_absorb_thrice(STATE, IN, IN_LEN, IN2, IN2_LEN, IN3, IN3_LEN)
#define xof256_squeeze(OUT, OUT_LEN, STATE)                                    \
  shake256_inc_squeeze(OUT, OUT_LEN, STATE)
#define xof256_squeezeblocks(OUT, OUTBLOCKS, STATE)                            \
  haetae_shake256_squeezeblocks(OUT, OUTBLOCKS, STATE)

// Stream: shake128/shake256 (incremental, common/fips202.c)
typedef shake128incctx stream128_state;
typedef shake256incctx stream256_state;

void haetae_shake128_stream_init(stream128_state *state,
                                 const uint8_t seed[HAETAE_SEEDBYTES],
                                 uint16_t nonce);
void haetae_shake256_stream_init(stream256_state *state,
                                 const uint8_t seed[HAETAE_CRHBYTES],
                                 uint16_t nonce);
void haetae_shake128_stream_squeezeblocks(uint8_t *output, size_t nblocks,
                                          stream128_state *state);
void haetae_shake256_stream_squeezeblocks(uint8_t *output, size_t nblocks,
                                          stream256_state *state);

#define STREAM128_BLOCKBYTES SHAKE128_RATE
#define STREAM256_BLOCKBYTES SHAKE256_RATE

#define stream128_init(STATE, SEED, NONCE)                                     \
  haetae_shake128_stream_init(STATE, SEED, NONCE)
#define stream128_squeezeblocks(OUT, OUTBLOCKS, STATE)                         \
  haetae_shake128_stream_squeezeblocks(OUT, OUTBLOCKS, STATE)
#define stream256_init(STATE, SEED, NONCE)                                     \
  haetae_shake256_stream_init(STATE, SEED, NONCE)
#define stream256_squeezeblocks(OUT, OUTBLOCKS, STATE)                         \
  haetae_shake256_stream_squeezeblocks(OUT, OUTBLOCKS, STATE)

#endif /* !HAETAE_SYMMETRIC_H */
