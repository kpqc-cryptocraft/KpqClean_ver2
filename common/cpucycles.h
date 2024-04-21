/* 
 * Duc Tri Nguyen (CERG GMU)
 * Modified from M1: 
 * https://gist.github.com/dougallj/5bafb113492047c865c0c8cfbc930155#file-m1_robsize-c-L390
 */

#ifndef m1cycles_h
#define m1cycles_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(__x86_64__) || defined(_M_X64)
    uint64_t cpucycles(void);
#elif defined(__aarch64__)
    void setup_rdtsc(void);
    extern unsigned long long int cpucycles(void);
#endif

#endif /* m1cycles_h */
