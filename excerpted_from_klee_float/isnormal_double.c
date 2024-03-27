// RUN: %llvmgcc %s -emit-llvm -O0 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out --exit-on-error %t1.bc > %t-output.txt 2>&1
// RUN: FileCheck -input-file=%t-output.txt %s
#include "klee/klee.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

int main() {
  double x;
  klee_make_symbolic(&x, sizeof(double), "x");
  if (klee_is_normal_double(x)) {
    assert(isnormal(x));
  } else {
    assert(!klee_is_normal_double(x));
    // forks in ``isnormal()``: could be 0, NaN, Inf, subnormal
    assert(!isnormal(x));
  }
}
// CHECK-NOT: silently concretizing (reason: floating point)
// CHECK: KLEE: done: completed paths = 5
