CC = gcc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./
NISTFLAGS += -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./
RM = /bin/rm

LDFLAGS=-lcrypto

COMMON_DIR= ../../../common
COMMON_FILES=$(COMMON_DIR)/randombytes.c $(COMMON_DIR)/cpucycles.c 
COMMON_HEADERS=$(COMMON_DIR)/randombytes.h  $(COMMON_DIR)/cpucycles.h 

KECCAK4XDIR=../../../common/keccak4x
KECCAK4XOBJ=KeccakP-1600-times4-SIMD256.o
KECCAK4X=$(KECCAK4XDIR)/$(KECCAK4XOBJ)
KECCAK4X_FILES= $(KECCAK4XDIR)/fips202x4.c
KECCAK4X_HEADERS= $(KECCAK4XDIR)/fips202x4.h 


KECCAKDIR=../../../common/Keccak_avx2
KECCAK_FILES= $(KECCAKDIR)/fips202.c $(KECCAKDIR)/KeccakP-1600-AVX2.o
KECCAK_HEADERS= $(KECCAKDIR)/fips202.h $(KECCAKDIR)/KeccakP-1600-SnP.h

BENCH_DIR= ../../kem_pke_bench
BENCH_FILES=$(BENCH_DIR)/SMAUG-T_KPQC_bench.c
GENKAT_FILES= $(BENCH_DIR)/SMAUG_PQCgenKAT_kem.c

SOURCES= ciphertext.c dg.c  hash.c hwt.c indcpa.c io.c kem.c key.c pack.c poly.c verify.c $(KECCAK4X_FILES)  $(KECCAK_FILES) 
HEADERS= align.h api.h ciphertext.h dg.h hash.h hwt.h indcpa.h io.h kem.h key.h pack.h parameters.h poly.h verify.h $(KECCAK4X_HEADERS) $(KECCAK_HEADERS) 

GENKAT_SOURCES= $(COMMON_DIR)/aes.c $(COMMON_DIR)/sha2.c $(COMMON_DIR)/rng.c $(COMMON_DIR)/fips202.c
GENKAT_HEADERS= $(COMMON_DIR)/aes.h $(COMMON_DIR)/sha2.h $(COMMON_DIR)/rng.h $(COMMON_DIR)/fips202.h


.PHONY: all test PQCgenKAT clean

all: \
	KPQC_bench \
	PQCgenKAT

KPQC_bench: $(COMMON_HEADERS) $(HEADERS) $(COMMON_FILES)  $(SOURCES) $(BENCH_FILES)
	$(CC) $(CFLAGS) -o $@ $(BENCH_FILES) $(SOURCES) $(COMMON_FILES) $(KECCAK4X) 

PQCgenKAT: $(GENKAT_HEADERS) $(HEADERS) $(GENKAT_SOURCES) $(SOURCES) $(GENKAT_FILES) 
	$(CC) $(NISTFLAGS) -o $@ $(GENKAT_FILES) $(SOURCES) $(GENKAT_SOURCES) $(KECCAK4X) 

clean:
	-$(RM) -f KpqC_bench
	-$(RM) -f PQCgenKAT
	rm -f *.rsp
	rm -f *.req
