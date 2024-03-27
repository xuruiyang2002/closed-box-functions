// RUN: %llvmgcc %s -emit-llvm -O0 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -internal-fabs=true --exit-on-error %t1.bc > %t-output.txt 2>&1
// RUN: FileCheck -input-file=%t-output.txt %s
#include "klee/klee.h"
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>

int main() {
  float x = 0.0f;
  klee_make_symbolic(&x, sizeof(float), "x");

  float result = fabsf(x);

  if (isnan(x)) {
    if (signbit(x)) {
      // CHECK-DAG: -ve nan
      printf("-ve nan\n");
    } else {
      // CHECK-DAG: +ve nan
      printf("+ve nan\n");
    }
    assert(!signbit(result));
    assert(isnan(result));
    return 0;
  }

  if (isinf(x)) {
    if (signbit(x)) {
      // CHECK-DAG: -ve inf
      printf("-ve inf\n");
    } else {
      // CHECK-DAG: +ve inf
      printf("+ve inf\n");
    }
    assert(!signbit(result));
    assert(isinf(result) == 1);
    return 0;
  }

  if (x == 0.0f) {
    if (signbit(x)) {
      // CHECK-DAG: -ve 0.0
      printf("-ve 0.0\n");
    } else {
      // CHECK-DAG: +ve 0.0
      printf("+ve 0.0\n");
    }
    assert(!signbit(result));
    assert(result == 0.0f);
    return 0;
  }

  // CHECK-DAG: result > 0.0
  printf("result > 0.0\n");
  assert(result > 0.0f);

  return 0;
}
// CHECK-DAG: KLEE: done: completed paths = 7
