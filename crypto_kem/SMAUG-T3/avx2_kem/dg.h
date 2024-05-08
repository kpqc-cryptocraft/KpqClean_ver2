#ifndef SMAUG_DG_H
#define SMAUG_DG_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "align.h"
#include "Keccak_avx2/fips202.h"
#include "keccak4x/fips202x4.h"
#include "parameters.h"
#include "poly.h"
#include "randombytes.h"
#include "verify.h"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// NOISE DISTRIBUTION ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// error distribution for LWE instances in public key generation:
// store probability table (CDF_TABLE)
// sample a single error from (RANDBITS)-length of random binary string

// A discrete error distribution close to the discrete Gaussian distribution
#define addGaussianError SMAUG_NAMESPACE(addGaussianError)
int addGaussianError(poly *op, uint64_t *seed);
#define addGaussianErrorVec SMAUG_NAMESPACE(addGaussianErrorVec)
void addGaussianErrorVec(polyvec *op, const uint8_t seed[CRYPTO_BYTES]);

#endif // SMAUG_DG_H
