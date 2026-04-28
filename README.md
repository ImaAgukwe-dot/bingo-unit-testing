# bingo-unit-testing
C++ unit testing assignment — CPSC2720, University of Lethbridge

## About

Written unit tests in C++ for a multi-class Bingo game library. Tests were 
validated against both a clean library and a buggy library to identify and 
document defects.

## What I Did

- Designed test cases using equivalence class partitioning to cover normal 
  behavior and edge cases across multiple classes
- Verified tests passed on the clean library and used them to detect bugs 
  in the buggy library
- Filed structured bug reports documenting replication steps, expected 
  behavior, and root cause
- Ran static analysis, style checks, and Valgrind memory leak detection 
  throughout development

## How to Run

```bash
# Compile and run tests against the clean library
make test_clean
./test_clean

# Compile and run tests against the buggy library
make test_buggy
./test_buggy

# Check for memory leaks
make memcheck_clean
```

## Tools & Technologies

- C++
- Google Test
- Valgrind
- GitLab CI (static analysis, style checks)
- Makefile / Linux environment
