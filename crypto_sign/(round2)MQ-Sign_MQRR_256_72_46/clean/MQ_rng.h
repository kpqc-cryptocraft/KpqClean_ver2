///
///  @file rng.h
///  @brief An AES256 CTR DRBG
///
///  Created by Bassham, Lawrence E (Fed) on 8/29/17.
///  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
///
///  An AES256 CTR DRBG
///

#include <stdio.h>
#include "../common/rng.h"


void
randombytes_init_with_state( AES256_CTR_DRBG_struct * states, unsigned char *entropy_input_48bytes );

int
randombytes_with_state( AES256_CTR_DRBG_struct * states, unsigned char *x, unsigned long long xlen);



