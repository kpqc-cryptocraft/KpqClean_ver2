CC = gcc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./
NISTFLAGS += -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./
RM = /bin/rm

LDFLAGS=-lcrypto

COMMON_DIR=../../../common
COMMON_FILES=$(COMMON_DIR)/randombytes.c $(COMMON_DIR)/sha2.c $(COMMON_DIR)/cpucycles.c
COMMON_HEADERS=$(COMMON_DIR)/randombytes.h $(COMMON_DIR)/sha2.h $(COMMON_DIR)/cpucycles.h

BENCH_DIR=../../kem_pke_bench
BENCH_FILES=$(BENCH_DIR)/PKE_PQC_bench.c
GENKAT_FILES= $(BENCH_DIR)/PQCgenKAT_pke.c

ASM_FILES=add.s baseinv.s basemul.s cbd.s invntt.s ntt.s pack.s reduce.s

SOURCES= $(ASM_FILES) pke.c poly.c symmetric.c verify.c consts.c $(COMMON_DIR)/aes256ctr.c
HEADERS= params.h pke.h poly.h symmetric.h verify.h $(COMMON_DIR)/aes256ctr.h

GENKAT_SOURCES= $(COMMON_DIR)/aes.c $(COMMON_DIR)/sha2.c $(COMMON_DIR)/rng.c
GENKAT_HEADERS= $(COMMON_DIR)/aes.h $(COMMON_DIR)/sha2.h $(COMMON_DIR)/rng.h

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


