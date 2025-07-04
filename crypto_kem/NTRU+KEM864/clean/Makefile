CC =gcc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -O3 -fomit-frame-pointer -I../../../common -I./
NISTFLAGS += -Wno-unused-result -O3 -fomit-frame-pointer -I../../../common -I./
RM = /bin/rm

# LDFLAGS=-lcrypto

COMMON_DIR=../../../common
COMMON_FILES=$(COMMON_DIR)/aes.c $(COMMON_DIR)/randombytes.c $(COMMON_DIR)/sha2.c $(COMMON_DIR)/cpucycles.c $(COMMON_DIR)/fips202.c
COMMON_HEADERS=$(COMMON_DIR)/aes.h $(COMMON_DIR)/randombytes.h $(COMMON_DIR)/sha2.h $(COMMON_DIR)/cpucycles.h $(COMMON_DIR)/fips202.h

BENCH_DIR=../../kem_pke_bench
BENCH_FILES=$(BENCH_DIR)/KEM_PQC_bench.c
GENKAT_FILES= $(BENCH_DIR)/PQCgenKAT_kem.c

SOURCES= kem.c poly.c ntt.c symmetric.c reduce.c verify.c
HEADERS= params.h kem.h poly.h ntt.h symmetric.h reduce.h verify.h

GENKAT_SOURCES= $(COMMON_DIR)/aes.c $(COMMON_DIR)/sha2.c $(COMMON_DIR)/rng.c $(COMMON_DIR)/fips202.c
GENKAT_HEADERS= $(COMMON_DIR)/aes.h $(COMMON_DIR)/sha2.h $(COMMON_DIR)/rng.h $(COMMON_DIR)/fips202.h

.PHONY: all KpqC_bench PQCgenKAT clean

all: \
	KpqC_bench \
	PQCgenKAT

KpqC_bench: $(COMMON_HEADERS) $(HEADERS) $(COMMON_FILES) $(SOURCES) $(BENCH_FILES)
	$(CC) $(CFLAGS) -o $@ $(BENCH_FILES) $(SOURCES) $(COMMON_FILES) 

PQCgenKAT: $(GENKAT_HEADERS) $(HEADERS) $(GENKAT_SOURCES) $(SOURCES) $(GENKAT_FILES)
	$(CC) $(NISTFLAGS) -o $@ $(GENKAT_FILES) $(SOURCES) $(GENKAT_SOURCES) $(LDFLAGS)
 
clean:
	-$(RM) -f KpqC_bench
	-$(RM) -f PQCgenKAT
	rm -f *.rsp
	rm -f *.req
