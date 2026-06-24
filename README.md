# KpqClean_ver2

Clean reference implementations of the Korean Post-Quantum Cryptography (KpqC) standardized algorithms.

## What is KpqClean?

This project was inspired by [PQClean](https://github.com/PQClean/PQClean).
We removed the dependencies of KpqC algorithms and unified them under a single build/test infrastructure (shared `common/`, NIST-standard KAT generators) so that they can be compared and used in the same environment.

The four algorithms below have been selected as the final standardized KpqC algorithms:

- **KEM:** NTRU+, SMAUG-T
- **DSA:** AIMer, HAETAE

## Source code versions used

| Algorithm | Variant | Reference version | Source |
|---|---|---|---|
| **NTRU+** | 768 / 864 / 1152 | commit `621c667` (2026-03-19) | <https://github.com/ntruplus/ntruplus/tree/main> |
| **SMAUG-T** |mode 1 / 3 / 5 | v1.2.0 `bbc463c` (code 2026-05-21) | <https://github.com/CryptoLabInc/SMAUG-T.git> |
| **AIMer** | 128f, 128s, 192f, 192s, 256f, 256s | `e47c497` (2026-01-30) | <https://github.com/samsungsds-research-papers/AIMer> |
| **HAETAE** | mode 2 / 3 / 5 | v1.1.2 `743c31d` (2026-02-05)| <https://github.com/CryptoLabInc/HAETAE> |

## Repository layout

```text
common/                       # shared sources (used by every algorithm)
  aes.c / aes.h               #   AES (KAT DRBG)
  cpucycles.c / cpucycles.h   #   benchmarking
  fips202.c / fips202.h       #   SHAKE / SHA-3 (PQClean style — shake*incctx)
  randombytes.c / .h          #   OS random
  rng.c / rng.h               #   NIST AES-CTR-DRBG (for KAT)
  sha2.c / sha2.h
  Keccak_avx2/, keccak4x/     #   AVX2 keccak

crypto_kem/
  NTRU+{768,864,1152}/clean/
  SMAUG-T{1,3,5}/clean/
  kem_pke_bench/
    KEM_PQC_bench.c           #   shared benchmark driver
    PQCgenKAT_kem.c           #   shared NIST KAT generator

crypto_sign/
  AIMer{128f,128s,192f,192s,256f,256s}/clean/
  HAETAE{2,3,5}/clean/
  sign_bench/
    Sign_KPQC_bench.c         #   shared benchmark driver
    PQCgenKAT_sign.c          #   shared NIST KAT generator (AIMer)
    HAETAE_PQCgenKAT_sign.c   #   HAETAE-only KAT generator
```

All algorithms use the headers and DRBG provided by `common/` (no duplicated `fips202.c` / `randombytes.c` per algorithm).

## How to use

### Compile command
Use the following command for KpqC benchmarking compile.

For Intel, Ryzen processors

    make
    ./KpqC_bench
    ./PQCgenKAT
    
    make clean

For Apple Silicon

    make
    sudo ./KpqC_bench
    ./PQCgenKAT
    
    make clean

## License

This repository is released under the MIT License (see [LICENSE](LICENSE)).
The bundled reference implementations (NTRU+, SMAUG-T, AIMer, HAETAE) are used under their upstream licenses (MIT). Original license/copyright headers are preserved in each source file.

## Contact

- MinJoo Sim — <minjoos9797@gmail.com>
- HwaJeong Seo — <hwajeong84@gmail.com>

## Contributors

- (Ph.D. student) MinJoo Sim
- (Ph.D. student) SiWoo Eum
- (Ph.D. student) GyeongJu Song
- (Master student) MinWoo Lee
- (Master student) SangWong Kim
- (Master student) Minho Song
- (Associate professor) HwaJeong Seo
