CC = gcc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./
NISTFLAGS += -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./  
RM = /bin/rm

LDFLAGS=-lcrypto


COMMON_DIR= ../../../common
COMMON_FILES= $(COMMON_DIR)/randombytes.c  $(COMMON_DIR)/cpucycles.c $(COMMON_DIR)/aes256ctr.c 
COMMON_HEADERS= $(COMMON_DIR)/randombytes.h  $(COMMON_DIR)/cpucycles.h $(COMMON_DIR)/aes256ctr.h 

BENCH_DIR=../../sign_bench
BENCH_FILES=$(BENCH_DIR)/Sign_KPQC_bench.c
GENKAT_FILES= $(BENCH_DIR)/PQCgenKAT_sign.c

KECCAK4XDIR=../../../common/keccak4x
KECCAK4XOBJ=KeccakP-1600-times4-SIMD256.o
KECCAK4X=$(KECCAK4XDIR)/$(KECCAK4XOBJ)




KECCAKDIR=../../../common/Keccak_avx2
KECCAK_FILES= $(KECCAKDIR)/fips202.c $(KECCAKDIR)/KeccakP-1600-AVX2.o
KECCAK_HEADERS= $(KECCAKDIR)/fips202.h $(KECCAKDIR)/KeccakP-1600-SnP.h


SOURCES= consts.c decompose.c encoding.c fft.c fixpoint.c  packing.c  poly.c polyfix.c polymat.c polyvec.c  $(KECCAK4XDIR)/fips202x4.c \
		 reduce.c sampler.c samplerx4.c	sign.c symmetric-shake.c f1600x4.S \
		 invntt.S ntt.S pointwise.S shuffle.S  keccakx4_vec.c $(KECCAK_FILES) 

HEADERS= align.h config.h consts.h decompose.h encoding.h fft.h  fixpoint.h ntt.h packing.h params.h poly.h  $(KECCAK4XDIR)/fips202x4.h  \
		polyfix.h polymat.h polyvec.h rans_byte.h reduce.h sampler.h sign.h symmetric.h shuffle.inc keccakx4_vec.h $(KECCAK_HEADERS)


GENKAT_SOURCES= $(COMMON_DIR)/aes.c $(COMMON_DIR)/sha2.c $(COMMON_DIR)/rng.c $(COMMON_DIR)/fips202.c
GENKAT_HEADERS= $(COMMON_DIR)/aes.h $(COMMON_DIR)/sha2.h $(COMMON_DIR)/rng.h $(COMMON_DIR)/fips202.h





.PHONY: all test PQCgenKAT clean

all: \
	KpqC_bench \
	PQCgenKAT


KpqC_bench: $(COMMON_HEADERS)  $(HEADERS) $(COMMON_FILES) $(SOURCES) $(BENCH_FILES)
	$(CC) $(CFLAGS) -o $@ $(BENCH_FILES) $(SOURCES) $(COMMON_FILES) $(KECCAK4X)

PQCgenKAT: $(GENKAT_HEADERS) $(HEADERS) $(GENKAT_SOURCES) $(SOURCES) $(GENKAT_FILES) 
	$(CC) $(NISTFLAGS) -o $@ $(GENKAT_FILES) $(SOURCES) $(GENKAT_SOURCES) $(KECCAK4X) 

clean:
	-$(RM) -f KpqC_bench
	-$(RM) -f PQCgenKAT
	rm -f *.rsp
	rm -f *.req
