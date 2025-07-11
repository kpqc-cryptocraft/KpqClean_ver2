#ifndef PARAMS_H
#define PARAMS_H


#define NTRUPLUS_N 576
#define NTRUPLUS_Q 3457

#define NTRUPLUS_SYMBYTES  32   /* size in bytes of hashes, and seeds */
#define NTRUPLUS_SSBYTES   32   /* size in bytes of shared key */
#define NTRUPLUS_POLYBYTES 864

#define NTRUPLUS_PUBLICKEYBYTES  NTRUPLUS_POLYBYTES
#define NTRUPLUS_SECRETKEYBYTES  ((NTRUPLUS_POLYBYTES << 1) + NTRUPLUS_SYMBYTES)
#define NTRUPLUS_CIPHERTEXTBYTES  NTRUPLUS_POLYBYTES

#endif
