CC = gcc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./
NISTFLAGS += -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./  
RM = /bin/rm

LDFLAGS=-lcrypto
BENCH_DIR=../../sign_bench
BENCH_FILES=$(BENCH_DIR)/Sign_KPQC_bench.c
GENKAT_FILES= $(BENCH_DIR)/PQCgenKAT_sign.c

COMMON_DIR=../../../common
COMMON_FILES= $(COMMON_DIR)/cpucycles.c $(COMMON_DIR)/randombytes.c
COMMON_HEADERS= $(COMMON_DIR)/cpucycles.h $(COMMON_DIR)/randombytes.h

KECCAK4XDIR=Keccak4x
KECCAK4XOBJ=KeccakP-1600-times4-SIMD256.o
KECCAK4X=$(KECCAK4XDIR)/$(KECCAK4XOBJ)

KECCAKDIR=../../../common/Keccak_avx2
KECCAK_FILES= $(KECCAKDIR)/fips202.c $(KECCAKDIR)/KeccakP-1600-AVX2.o
KECCAK_HEADERS= $(KECCAKDIR)/fips202.h $(KECCAKDIR)/KeccakP-1600-SnP.h


SOURCES= field.c aim2.c hash.c tree.c sign.c $(KECCAK_FILES) $(KECCAK4XDIR)/KeccakP-1600-times4-SIMD256.c
HEADERS= field.h aim2.h hash.h tree.h params.h crypto_declassify.h api.h sign.h $(KECCAK_HEADERS) $(KECCAK4XDIR)/KeccakP-1600-times4-SnP.h
 
GENKAT_SOURCES= $(COMMON_DIR)/aes.c $(COMMON_DIR)/sha2.c $(COMMON_DIR)/rng.c $(COMMON_DIR)/fips202.c
GENKAT_HEADERS= $(COMMON_DIR)/aes.h $(COMMON_DIR)/sha2.h $(COMMON_DIR)/rng.h $(COMMON_DIR)/fips202.h

.PHONY: all KpqC_bench PQCgenKAT clean

all: \
	KpqC_bench \
	PQCgenKAT

KpqC_bench: $(COMMON_HEADERS) $(HEADERS) $(COMMON_FILES) $(SOURCES) $(BENCH_FILES)
	$(CC) $(CFLAGS) -o $@ $(BENCH_FILES) $(SOURCES) $(COMMON_FILES) 

PQCgenKAT: $(GENKAT_HEADERS) $(HEADERS) $(GENKAT_SOURCES) $(SOURCES) $(GENKAT_FILES)
	$(CC) $(NISTFLAGS) -o $@ $(GENKAT_FILES) $(SOURCES) $(GENKAT_SOURCES)
 
clean:
	-$(RM) -f KpqC_bench
	-$(RM) -f PQCgenKAT
	rm -f *.rsp
	rm -f *.req
