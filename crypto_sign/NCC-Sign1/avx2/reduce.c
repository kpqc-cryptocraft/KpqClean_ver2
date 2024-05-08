#include <stdint.h>
#include "params.h"
#include "reduce.h"

#if NIMS_MODE == 2
#define MONT 83081 // 2^32 % Q
#define QINV 1554761515 // -q^(-1) mod 2^32
#define R2 5619074 // 2^64 % Q

#elif NIMS_MODE == 3
#define MONT 6123008 // 2^32 % Q
#define QINV 3813543687 // -q^(-1) mod 2^32
#define R2 1441797 // 2^64 % Q

#elif NIMS_MODE == 5
#define MONT 6424230 // 2^32 % Q
#define QINV 578884571 // -q^(-1) mod 2^32
#define R2 3645001 // 2^64 % Q


// #elif NIMS_TRI_NTT_MODE == 1
// #define MONT 1781889 // 2^32 % Q
// #define QINV 2245397889 // q^(-1) mod 2^32
// #define R2 2742207 // 2^64 % Q

// #elif NIMS_TRI_NTT_MODE == 3
// #define MONT 3940353 // 2^32 % Q
// #define QINV 2080628225 // q^(-1) mod 2^32
// #define R2 1946999 // 2^64 % Q

// #elif NIMS_TRI_NTT_MODE == 5
// #define MONT 15873 // 2^32 % Q
// #define QINV 260030465 // q^(-1) mod 2^32
// #define R2 8207332 // 2^64 % Q

#endif

// uint32_t montgomery_reduce(uint64_t a) {
//   __uint128_t t;

//   int64_t b;

//   t = a * QINV;
//   t &= 0xFFFFFFFF;
//   t *= Q;
//   t = a + t;
//   b = t >> 32;
//   b-= ((Q-b) >> 63) & Q;

//   return (uint32_t)b;
// }

int32_t montgomery_reduce(int64_t a)
{
    int32_t t;
    t = (int32_t)a * QINV;
    t = (a - (int64_t)t * Q) >> 32;
    return t;
}
#include "stdio.h"
void printt_256(__m256i a)
{
    int64_t* a_64=(int64_t*)&a;
    printf("%016lx %016lx %016lx %016lx\n",a_64[3],a_64[2],a_64[1],a_64[0]);
}
__m256i montgomery_reduce_avx(__m256i a)
{
    __m256i Qx4 = _mm256_set1_epi64x(Q);
    __m256i QINVx4 = _mm256_set1_epi64x(QINV);

    __m256i aQINV = _mm256_mul_epi32(a,QINVx4);

    a = _mm256_srli_epi64(_mm256_sub_epi64(a, _mm256_mul_epi32(aQINV, Qx4)),32);

    return a;
}

// uint32_t to_mont(int32_t a) {
//   uint64_t t;
//   uint32_t a0=a;
 
//   a0+= (a >> 31) & Q;
//   t = (uint64_t)a0 * (uint64_t)R2;

//   return (uint32_t)montgomery_reduce(t);
// }

// uint32_t from_mont(int32_t a){
//   return (int32_t)montgomery_reduced(a);
// }

// uint32_t reduce32(int64_t a) {
//   int64_t t;
//   uint32_t res;

//   t = a%Q;
//   t+= (t >> 63) & Q;
//   res = (uint32_t)t;

//   return res;
// }

int32_t caddq(int32_t a)
{
    a += (a >> 31) & Q;
    return a;
}

int32_t csubq(int32_t a)
{
    a -= Q;
    a += ((int32_t)a >> 31) & Q;
    return a;
}

int32_t freeze(int32_t a)
{
    a = reduce32(a);
    a = caddq(a);
    return a;
}

// uint32_t mod_add(uint32_t a, uint32_t b)
// {
//     int32_t t;
//     t=(a+b);
//     t=t-Q;
//     t += (t >> 31) & Q;

//     return (uint32_t)t;
// }
int32_t mod_add(int32_t a, int32_t b)
{
    int32_t t;
    t = (a + b);
    t = t - Q;
    t += (t >> 31) & Q;
    t += (t >> 31) & Q;
    t += (t >> 31) & Q;

    return (uint32_t)t;
}
// uint32_t mod_sub(uint32_t a, uint32_t b)
// {
//     int32_t t;
//     t=a-b;
//     t += (t >> 31) & Q;

//     return (uint32_t)t;
// }
int32_t mod_sub(int32_t a, int32_t b)
{
    int32_t t;
    t = a - b;
    t = t - Q;
    t += (t >> 31) & Q;
    t += (t >> 31) & Q;
    t += (t >> 31) & Q;

    return (uint32_t)t;
}
/*************************************************
* Name:        reduce32
*
* Description: For finite field element a with a <= 2^{31} - 2^{22} - 1,
*              compute r \equiv a (mod Q) such that -6283009 <= r <= 6283007.
*
* Arguments:   - int32_t: finite field element a
*
* Returns r.
**************************************************/
int32_t reduce32(int32_t a)
{
    int32_t t;

    t = (a + (1 << 22)) >> 23;
    t = a - t * Q;
    //t = a % Q;
    return t;
}
#define _mm256_blendv_epi32(a,b,mask) \
        _mm256_castps_si256(_mm256_blendv_ps(_mm256_castsi256_ps(a), \
                                             _mm256_castsi256_ps(b), \
                                             _mm256_castsi256_ps(mask)));

__m256i reduce32_avx(__m256i a)
{
    __m256i t,temp;
    __m256i Qx4 = _mm256_set1_epi64x(Q);
    __m256i _22 = _mm256_set_epi32(0, 0, 0, 0x400000, 0, 0x400000, 0, 0x400000);
    __m256i t1 = _mm256_set1_epi64x((int64_t)0x7fffff00000000);

    temp = _mm256_add_epi32(a, _22);
    t = _mm256_slli_epi64(temp, 32);
    temp = _mm256_blendv_epi32(temp, t1, t);
    t = _mm256_srli_epi64(temp, 23);

    t = _mm256_sub_epi32(a, _mm256_mullo_epi32(t, Qx4));

    return t;
}

__m256i reduce32_avx_4(__m256i a)
{
    __m256i t,temp;
    __m256i Qx4 = _mm256_set1_epi64x(Q);
    __m256i _22 = _mm256_set_epi32(0, 0x400000, 0, 0x400000, 0, 0x400000, 0, 0x400000);
    __m256i t1 = _mm256_set1_epi64x((int64_t)0x7fffff00000000);

    temp = _mm256_add_epi32(a, _22);
    t = _mm256_slli_epi64(temp, 32);
    temp = _mm256_blendv_epi32(temp, t1, t);
    t = _mm256_srli_epi64(temp, 23);

    t = _mm256_sub_epi32(a, _mm256_mullo_epi32(t, Qx4));

    return t;
}
