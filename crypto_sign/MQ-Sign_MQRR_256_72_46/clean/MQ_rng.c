//
//  rng.c
//
//  Created by Bassham, Lawrence E (Fed) on 8/29/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//

#include <string.h>
#include "../common/rng.h"


void
randombytes_init_with_state( AES256_CTR_DRBG_struct * states, unsigned char *entropy_input_48bytes )
{

    unsigned char   seed_material[48];
    memcpy(seed_material, entropy_input_48bytes, 48);

    memset(states->Key, 0x00, 32);
    memset(states->V, 0x00, 16);
    AES256_CTR_DRBG_Update(seed_material, states->Key, states->V);
    states->reseed_counter = 1;
}

int
randombytes_with_state( AES256_CTR_DRBG_struct * states, unsigned char *x, unsigned long long xlen)
{

    unsigned char   block[16];
    int             i = 0;

    while ( xlen > 0 ) {
        //increment V
        for (int j=15; j>=0; j--) {
            if ( states->V[j] == 0xff )
                states->V[j] = 0x00;
            else {
                states->V[j]++;
                break;
            }
        }
        AES256_ECB(states->Key, states->V, block);
        if ( xlen > 15 ) {
            memcpy(x+i, block, 16);
            i += 16;
            xlen -= 16;
        }
        else {
            memcpy(x+i, block, xlen);
            xlen = 0;
        }
    }
    AES256_CTR_DRBG_Update(NULL, states->Key, states->V);
    states->reseed_counter++;

    return RNG_SUCCESS;
}


