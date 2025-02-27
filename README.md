# Matrix chain

## Introduction

This project is the implementation of chain of matrices, that are multiplied in the optimal order.

## Build and Run

Cloning repository:
```
git clone --recursive https://github.com/ogkisque/Matrix-Chain.git
git submodule update --init --recursive
cd libhayai
git fetch
cd ..
cd Matrix
git fetch
```

If you want to build the project, write this in the project directory:
```
cmake -S . -B build
cmake --build build
```

After that, you can run main target program:

```
./build/src/main_chain
```

## Tests
### Unit

If you want to run unit tests, generate Makefiles with the WITH_TESTS flag:
```
cmake [...] -DWITH_TESTS=1
```

Then build `tests` target:
```
cmake --build build --target tests
```

After that, run:
```
./build/tests/tests
```

### End to end

If you want to run end-to-end tests, type it:
```
python3 tests/check_end_to_end.py
```

### Benchmarks

Also you can compare the performance of multiply in optimal and direct orders.

Generate Makefiles with the WITH_BENCHMARKS flag:
```
cmake [...] -DWITH_BENCHMARKS=1
```

Then build `benchs` target:
```
cmake --build build --target benchs
```

Finally, run the program:
```
./build/benchs/benchs
```
