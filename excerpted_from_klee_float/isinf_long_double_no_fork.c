// RUN: %llvmgcc %s -emit-llvm -O0 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out %t1.bc > %t-output.txt 2>&1
// RUN: FileCheck -input-file=%t-output.txt %s
// REQUIRES: x86_64

#include "klee/klee.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

int main() {
  long double x;
  klee_make_symbolic(&x, sizeof(long double), "x");
  klee_assume(isinf(x));
  assert(klee_is_infinite_long_double(x));
}
// CHECK-NOT: invalid klee_assume call (provably false)
// CHECK: KLEE: done: completed paths = 1
