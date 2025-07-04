#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include <stddef.h>
#include <stdint.h>
#include "params.h"

#define NTRUPLUS_NAMESPACE(s) kpqclean_ntruplus1152_clean_##s

#define hash_f NTRUPLUS_NAMESPACE(hash_f)
void hash_f(uint8_t *buf, const uint8_t *msg);

#define hash_g NTRUPLUS_NAMESPACE(hash_g)
void hash_g(uint8_t *buf, const uint8_t *msg);

#define hash_h_kem NTRUPLUS_NAMESPACE(hash_h_kem)
void hash_h_kem(uint8_t *buf, const uint8_t *msg);

#endif /* SYMMETRIC_H */