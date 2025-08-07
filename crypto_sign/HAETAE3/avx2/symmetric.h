#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include "params.h"
#include <stdint.h>
#include "Keccak_avx2/fips202.h"

// Cryptographic XOF function: shake256
typedef keccak_state xof256_state;

#define haetae_shake256_absorb_twice                                           \
    HAETAE_NAMESPACE(haetae_shake256_absorb_twice)
void haetae_shake256_absorb_twice(keccak_state *state, const uint8_t *in1,
                                size_t in1len, const uint8_t *in2, size_t in2len);

#define haetae_shake256_absorb_once                                           \
    HAETAE_NAMESPACE(haetae_shake256_absorb_once)
void haetae_shake256_absorb_once(xof256_state *state, const uint8_t *in1,
                                 size_t in1len);

#define haetae_shake256_squeezeblocks                     \
    HAETAE_NAMESPACE(haetae_shake256_squeezeblocks)
void haetae_shake256_squeezeblocks(uint8_t *output, size_t nblocks,
                                   xof256_state *state);

#define XOF256_BLOCKBYTES SHAKE256_RATE

#define xof256_absorbe_once(STATE, IN, IN_LEN)                                  \
    haetae_shake256_absorb_once(STATE, IN, IN_LEN)
#define xof256_absorbe_twice(STATE, IN, IN_LEN, IN2, IN2_LEN)                   \
    haetae_shake256_absorb_twice(STATE, IN, IN_LEN, IN2, IN2_LEN) 
#define xof256_squeeze(OUT, OUT_LEN, STATE)                                     \
    shake256_squeeze(OUT, OUT_LEN, STATE)
#define xof256_squeezeblocks(OUT, OUTBLOCKS, STATE)                             \
    haetae_shake256_squeezeblocks(OUT, OUTBLOCKS, STATE)


// Stream function: aes256 or shake128|256
#ifdef HAETAE_USE_AES // stream: aes256

#include "aes256ctr.h"

typedef aes256ctr_ctx stream128_state;
typedef aes256ctr_ctx stream256_state;

#define STREAM128_BLOCKBYTES AES256CTR_BLOCKBYTES
#define STREAM256_BLOCKBYTES AES256CTR_BLOCKBYTES

#define stream128_init(STATE, SEED, NONCE) \
        aes256ctr_init(STATE, SEED, NONCE)
#define stream128_squeezeblocks(OUT, OUTBLOCKS, STATE) \
        aes256ctr_squeezeblocks(OUT, OUTBLOCKS, STATE)
#define stream256_init(STATE, SEED, NONCE) \
        aes256ctr_init(STATE, SEED, NONCE)
#define stream256_squeezeblocks(OUT, OUTBLOCKS, STATE) \
        aes256ctr_squeezeblocks(OUT, OUTBLOCKS, STATE)

#else // stream: shake128 and shake256

typedef keccak_state stream128_state;
typedef keccak_state stream256_state;

#define haetae_shake128_stream_init                                            \
    HAETAE_NAMESPACE(haetae_shake128_stream_init)
void haetae_shake128_stream_init(keccak_state *state,
                                 const uint8_t seed[SEEDBYTES], uint16_t nonce);

#define haetae_shake128_stream_squeezeblocks                                           \
    HAETAE_NAMESPACE(haetae_shake128_stream_squeezeblocks)
void haetae_shake128_stream_squeezeblocks(uint8_t *output, size_t nblocks, 
                                           stream128_state *state);


#define haetae_shake256_stream_init                                            \
    HAETAE_NAMESPACE(haetae_shake256_stream_init)
void haetae_shake256_stream_init(keccak_state *state,
                                 const uint8_t seed[CRHBYTES], uint16_t nonce);

#define haetae_shake256_stream_squeezeblocks                                           \
    HAETAE_NAMESPACE(haetae_shake256_stream_squeezeblocks)
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

#endif // stream

#endif //SYMMETRIC_H
