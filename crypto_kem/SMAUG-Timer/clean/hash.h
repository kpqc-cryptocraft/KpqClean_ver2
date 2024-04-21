#ifndef TIMER_HASH_H
#define TIMER_HASH_H

#include "fips202.h"
#include "parameters.h"

#define hash_h(OUT, IN, INBYTES) sha3_256(OUT, IN, INBYTES)
#define hash_g(OUT, OUTBYTES, IN1, IN1BYTES, IN2, IN2BYTES)                    \
    shake256_absorb_twice_squeeze(OUT, OUTBYTES, IN1, IN1BYTES, IN2, IN2BYTES)

#define shake256_absorb_twice_squeeze                                          \
    TIMER_NAMESPACE(shake256_absorb_twice_squeeze)
void shake256_absorb_twice_squeeze(uint8_t *out, size_t out_bytes,
                                   const uint8_t *in1, size_t in1_bytes,
                                   const uint8_t *in2, size_t in2_bytes);


#define shake256_absorb_once                                          \
    TIMER_NAMESPACE(shake256_absorb_once)
void shake256_absorb_once(shake256incctx *state, const uint8_t *in1, size_t in1_bytes);

                                   


#endif // TIMER_HASH_H
