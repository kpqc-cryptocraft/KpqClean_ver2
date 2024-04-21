#include <stdint.h>
#include "params.h"
#include "reduce.h"

#if NIMS_MODE == 1
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


#elif NIMS_TRI_NTT_MODE == 1
#define MONT 1781889 // 2^32 % Q
#define QINV 2245397889 // q^(-1) mod 2^32
#define R2 2742207 // 2^64 % Q

#elif NIMS_TRI_NTT_MODE == 3
#define MONT 3940353 // 2^32 % Q
#define QINV 2080628225 // q^(-1) mod 2^32
#define R2 1946999 // 2^64 % Q

#elif NIMS_TRI_NTT_MODE == 5
#define MONT 15873 // 2^32 % Q
#define QINV 260030465 // q^(-1) mod 2^32
#define R2 8207332 // 2^64 % Q

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

int32_t montgomery_reduce(int64_t a) {
  int32_t t;

  t = (int64_t)(int32_t)a*QINV;
  t = (a - (int64_t)t*Q) >> 32;
  return t;
}


int32_t caddq(int32_t a) {
  a += (a >> 31) & Q; 
  return a;
}

int32_t csubq(int32_t a) {
  a -= Q;
  a += ((int32_t)a >> 31) & Q;
  return a;
}

int32_t freeze(int32_t a) {
  a = reduce32(a);
  a = caddq(a);
  return a;
}

int32_t mod_add(int32_t a, int32_t b)
{
    int32_t t;
    t=(a+b);
    t=t-Q;
    t += (t >> 31) & Q;
    t += (t >> 31) & Q;
    t += (t >> 31) & Q;

    return (uint32_t)t;
}


int32_t mod_sub(int32_t a, int32_t b)
{
    int32_t t;
    t=a-b;
    t=t-Q;
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
int32_t reduce32(int32_t a) {
  int32_t t;

  t = (a + (1 << 22)) >> 23;
  t = a - t*Q;
  //t=a%Q;
  return t;
}
