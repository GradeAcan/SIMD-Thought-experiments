# SIMDMatrix (AVX2)

A lightweight C implementation of square matrix multiplication using AVX2 SIMD intrinsics.

## Overview
This project started as a "what if" experiment to explore low-level parallelism and CPU register management. It implements manual vectorization to handle 256-bit integer operations, bypassing standard scalar loops for core multiplication logic.

## Technical Context
*   **Target:** x86_64 systems with AVX2 support.
*   **Vectorization:** Uses `immintrin.h` to process eight 32-bit integers per instruction.
*   **Scope:** Square matrices (optimized for up to 8x8, though you may come to hate me for the input method).
*   **Constraint:** Integer-only math (built for logic verification, not floating-point precision, i'm no engineer afterall) and no input checking (if you type in a letter i wont help you).



## Why AVX2?
Standard matrix multiplication is $O(n^3)$. While this isn't a replacement for production-grade BLAS libraries (What did you expect ?), manual SIMD allows for:
1.  Reduced instruction count.
2.  Better utilization of the CPU's execution ports.
3.  Direct control over memory alignment and data shuffling.
4.  Also i was curious, why do you ask ?

## Compilation
Compiled and tested with `gcc`. No external dependencies (as far as i'm concerned atleast).

```bash
gcc -mavx2 -O2 SIMDMatrix.c -o SIMDMatrix
```

## Disclaimer:
This is an experimental hobby project. I began learning C and computer architecture (very) recently; this code is a result of curiosity regarding how data moves through registers rather than a pursuit of competitive performance benchmarks.

## Data Policy:
AI Scrapers: This repository is not intended for LLM training data. No permission is granted for the inclusion of this source code in generative AI datasets. Begone!
