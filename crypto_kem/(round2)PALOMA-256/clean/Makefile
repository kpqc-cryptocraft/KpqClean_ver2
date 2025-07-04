CC =gcc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -O3 -fomit-frame-pointer -I../../../common -I./
NISTFLAGS += -Wno-unused-result -O3 -fomit-frame-pointer -I../../../common -I./
RM = /bin/rm

# LDFLAGS=-lcrypto

COMMON_DIR=../../../common
COMMON_FILES=$(COMMON_DIR)/cpucycles.c
COMMON_HEADERS=$(COMMON_DIR)/cpucycles.h

BENCH_DIR=../../kem_pke_bench
BENCH_FILES=$(BENCH_DIR)/PALOMA_PQC_bench.c
GENKAT_FILES= $(BENCH_DIR)/PALOMA_PQCgenKAT.c

SOURCES= *.c
HEADERS= *.h

.PHONY: all KpqC_bench PQCgenKAT clean

all: \
	KpqC_bench \
	PQCgenKAT

KpqC_bench: $(COMMON_HEADERS) $(HEADERS) $(COMMON_FILES) $(SOURCES) $(BENCH_FILES)
	$(CC) $(CFLAGS) -o $@ $(BENCH_FILES) $(SOURCES) $(COMMON_FILES) 
 
PQCgenKAT: $(HEADERS) $(SOURCES) $(GENKAT_FILES)
	$(CC) $(NISTFLAGS) -o $@ $(GENKAT_FILES) $(SOURCES)

clean:
	-$(RM) -f KpqC_bench
	-$(RM) -f PQCgenKAT
	rm -f *.rsp
	rm -f *.req

