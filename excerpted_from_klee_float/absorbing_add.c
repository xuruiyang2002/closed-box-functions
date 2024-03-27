// RUN: %llvmgcc %s -emit-llvm -O0 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out --exit-on-error %t1.bc > %t-output.txt 2>&1
// RUN: FileCheck -input-file=%t-output.txt %s
#include "klee/klee.h"
#include <stdio.h>

// This test is based off an example from
// "Symbolic execution of floating-point computations"
// by Bernard Botella, Arnaud Gotlieb, and Claude Michel
int main() {
  float x, y, z;
  klee_make_symbolic(&x, sizeof(float), "x");
  klee_assume(x > 0.0f); // This also implies x isn't a NaN
  y = 1.0e12f;
  z = x + y;
  if ( z == y ) {
    // Note if we use reals to approximate floats this branch won't be feasible
    printf("add x absorbed\n");
  } else {
    printf("addition visible\n");
  }
  return 0;
}
// CHECK-NOT: silently concretizing (reason: floating point)
// CHECK: KLEE: done: completed paths = 2
