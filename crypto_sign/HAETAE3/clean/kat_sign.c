// SPDX-License-Identifier: MIT

#include "api.h"
#include "kat_api.h"

int kat_crypto_sign_keypair(uint8_t *pk, uint8_t *sk, uint8_t *seed) {
  return crypto_sign_keypair_internal(pk, sk, seed);
}

int kat_crypto_sign_signature(uint8_t *sig, size_t *siglen, const uint8_t *m,
                              size_t mlen, const uint8_t *pre, size_t prelen,
                              const uint8_t *rnd, const uint8_t *sk) {
  return crypto_sign_signature_internal(sig, siglen, m, mlen, pre, prelen, rnd,
                                        sk);
}

int kat_crypto_sign_verify(const uint8_t *sig, size_t siglen, const uint8_t *m,
                           size_t mlen, const uint8_t *pre, size_t prelen,
                           const uint8_t *pk) {
  return crypto_sign_verify_internal(sig, siglen, m, mlen, pre, prelen, pk);
}
