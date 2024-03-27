// RUN: %llvmgcc %s -emit-llvm -O0 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out --exit-on-error %t1.bc > %t-output.txt 2>&1
// RUN: FileCheck -input-file=%t-output.txt %s
// REQUIRES: x86_64
#include "klee/klee.h"
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

int main() {
  long double x = 0.0;
  klee_make_symbolic(&x, sizeof(long double), "x");
  long double result = klee_sqrt_long_double(x);

  if (isnan(x)) {
    assert(isnan(result));
    return 0;
  }

  if (x < 0.0l) {
    assert(isnan(result));
    return 0;
  }

  if (isinf(x)) {
    assert(isinf(result) == 1);
    return 0;
  }

  if (x == 0.0l) {
    assert(result == 0.0l);
    // check sign bit sqrt(-0.0) == -0.0
    if (signbit(x)) {
      assert(signbit(result));
    }
    return 0;
  }

  assert(x > 0.0l);
  return 0;
}
// CHECK: KLEE: done: completed paths = 6
