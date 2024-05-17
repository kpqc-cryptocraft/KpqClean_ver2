CC = gcc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./
NISTFLAGS += -mavx2 -mbmi2 -mpopcnt -maes \
  -march=native -mtune=native -O3 -fomit-frame-pointer -I../../../common -I./
RM = /bin/rm

# LDFLAGS=-lcrypto

COMMON_DIR=../../../common
COMMON_FILES=$(COMMON_DIR)/cpucycles.c $(COMMON_DIR)/fips202.c
COMMON_HEADERS=$(COMMON_DIR)/cpucycles.h $(COMMON_DIR)/fips202.h 

BENCH_DIR=../../sign_bench
BENCH_FILES=$(BENCH_DIR)/MQsign_KPQC_bench.c
GENKAT_FILES= $(BENCH_DIR)/MQsign_PQCgenKAT_sign.c


SOURCES= aes.c blas_comm.c blas_matrix_avx2.c blas_matrix_ref.c blas_matrix_sse.c blas_matrix.c gf16.c mqs_keypair_computation_simd.c mqs_keypair_computation.c mqs_keypair.c mqs_simd.c parallel_matrix_op_avx2.c parallel_matrix_op.c rng.c sign.c utils_hash.c utils_prng.c utils.c
  
HEADERS= aes.h blas_avx2.h blas_comm.h blas_config.h blas_matrix_avx2.h blas_matrix_ref.h blas_matrix_sse.h blas_matrix.h blas_sse.h blas_u32.h blas_u64.h blas.h gf16_avx2.h gf16_sse.h gf16_tabs.h gf16_u64.h gf16.h hash_len_config.h mpkc_avx2.h mpkc.h mqs_blas_simd.h mqs_blas.h mqs_config.h mqs_keypair_computation_simd.h mqs_keypair_computation.h mqs_keypair.h mqs.h parallel_matrix_op_avx2.h parallel_matrix_op.h rng.h utils_hash.h utils_malloc.h utils_prng.h utils.h

GENKAT_SOURCES= $(COMMON_DIR)/aes.c $(COMMON_DIR)/sha2.c $(COMMON_DIR)/fips202.c
GENKAT_HEADERS= $(COMMON_DIR)/aes.h $(COMMON_DIR)/sha2.h $(COMMON_DIR)/fips202.h

.PHONY: all test PQCgenKAT clean

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