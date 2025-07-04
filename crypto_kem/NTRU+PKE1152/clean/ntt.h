#ifndef NTT_H
#define NTT_H

#include <stdint.h>
#include "params.h"

#define NTRUPLUS_NAMESPACE(s) kpqclean_ntruplus1152_clean_##s

#define zetas NTRUPLUS_NAMESPACE(zetas)
extern const int16_t zetas[288];

#define ntt NTRUPLUS_NAMESPACE(ntt)
void ntt(int16_t r[NTRUPLUS_N], const int16_t a[NTRUPLUS_N]);

#define invntt NTRUPLUS_NAMESPACE(invntt)
void invntt(int16_t r[NTRUPLUS_N], const int16_t a[NTRUPLUS_N]);

#define baseinv NTRUPLUS_NAMESPACE(baseinv)
int baseinv(int16_t r[4], const int16_t a[4], int16_t zeta);

#define basemul NTRUPLUS_NAMESPACE(basemul)
void basemul(int16_t r[4], const int16_t a[4], const int16_t b[4], int16_t zeta);

#define basemul_add NTRUPLUS_NAMESPACE(basemul_add)
void basemul_add(int16_t r[4], const int16_t a[4], const int16_t b[4], const int16_t c[4], int16_t zeta);

#endif