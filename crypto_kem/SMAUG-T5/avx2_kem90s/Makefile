CC = gcc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./
NISTFLAGS += -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./
RM = /bin/rm

LDFLAGS=-lcrypto

COMMON_DIR= ../../../common
COMMON_FILES=$(COMMON_DIR)/randombytes.c $(COMMON_DIR)/cpucycles.c $(COMMON_DIR)/sha2.c
COMMON_HEADERS=$(COMMON_DIR)/randombytes.h  $(COMMON_DIR)/cpucycles.h $(COMMON_DIR)/sha2.h

KECCAKAVXDIR = ../../../common/Keccak_avx2

BENCH_DIR= ../../kem_pke_bench
BENCH_FILES=$(BENCH_DIR)/KEM_PQC_bench.c
GENKAT_FILES= $(BENCH_DIR)/PQCgenKAT_kem.c

ASM_FILES= basemul.S invntt.S ntt.S $(KECCAKAVXDIR)/KeccakP-1600-AVX2.s

SOURCES= $(ASM_FILES) ciphertext.c cbd.c dg.c consts7681.c consts10753.c hash.c hwt.c indcpa.c io.c kem.c key.c pack.c poly.c verify.c ntt.c $(COMMON_DIR)/aes256ctr.c $(KECCAK_FILES) $(KECCAKAVXDIR)/fips202.c
HEADERS= align.h api.h ciphertext.h cbd.h dg.h hash.h hwt.h indcpa.h io.h kem.h key.h pack.h parameters.h poly.h verify.h ntt.h  $(COMMON_DIR)/aes256ctr.h $(KECCAK_HEADERS) $(KECCAKAVXDIR)/fips202.h

GENKAT_SOURCES= $(COMMON_DIR)/aes.c $(COMMON_DIR)/sha2.c $(COMMON_DIR)/rng.c $(COMMON_DIR)/fips202.c
GENKAT_HEADERS= $(COMMON_DIR)/aes.h $(COMMON_DIR)/sha2.h $(COMMON_DIR)/rng.h $(COMMON_DIR)/fips202.h


.PHONY: all test PQCgenKAT clean

all: \
	KpqC_bench \
	PQCgenKAT

KpqC_bench: $(COMMON_HEADERS) $(HEADERS) $(COMMON_FILES)  $(SOURCES) $(BENCH_FILES)
	$(CC) $(CFLAGS) -o $@ $(BENCH_FILES) $(SOURCES) $(COMMON_FILES)

PQCgenKAT: $(GENKAT_HEADERS) $(HEADERS) $(GENKAT_SOURCES) $(SOURCES) $(GENKAT_FILES) 
	$(CC) $(NISTFLAGS) -o $@ $(GENKAT_FILES) $(SOURCES) $(GENKAT_SOURCES) 

clean:
	-$(RM) -f KpqC_bench
	-$(RM) -f PQCgenKAT
	rm -f *.rsp
	rm -f *.req
