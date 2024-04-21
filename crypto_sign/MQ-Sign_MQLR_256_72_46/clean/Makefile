CC =gcc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -O3 -fomit-frame-pointer -I../../../common -I./
NISTFLAGS += -Wno-unused-result -O3 -fomit-frame-pointer -I../../../common -I./
RM = /bin/rm

COMMON_DIR=../../../common
COMMON_FILES=$(COMMON_DIR)/cpucycles.c $(COMMON_DIR)/aes.c $(COMMON_DIR)/fips202.c $(COMMON_DIR)/rng.c
COMMON_HEADERS=$(COMMON_DIR)/cpucycles.h $(COMMON_DIR)/aes.h $(COMMON_DIR)/fips202.h $(COMMON_DIR)/rng.h

BENCH_DIR=../../sign_bench
BENCH_FILES=$(BENCH_DIR)/MQsign_KPQC_bench.c
GENKAT_FILES= $(BENCH_DIR)/MQsign_PQCgenKAT_sign.c

SOURCES= blas_comm.c blas_matrix_ref.c blas_matrix.c mqs_keypair_computation.c mqs_keypair.c mqs.c parallel_matrix_op.c sign.c utils_hash.c utils_prng.c utils.c
HEADERS= api.h blas_comm.h blas_matrix_ref.h blas_matrix.h blas_u32.h blas.h gf16.h hash_len_config.h mpkc.h mqs_blas.h mqs_config.h mqs_keypair_computation.h mqs_keypair.h mqs.h parallel_matrix_op.h utils_hash.h utils_malloc.h utils_prng.h utils.h

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
