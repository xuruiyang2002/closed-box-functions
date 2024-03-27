// RUN: %llvmgcc %s -emit-llvm -O0 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out --exit-on-error %t1.bc > %t-output.txt 2>&1
// RUN: FileCheck -input-file=%t-output.txt %s
#include "klee/klee.h"
#include <assert.h>
#include <math.h>

int main() {
  float f;
  klee_make_symbolic(&f, sizeof(f), "f");
  float result = -f;
  if (signbit(f)) {
    assert(!signbit(result));
  } else {
    if (!isnan(f))
      assert(signbit(result));
  }
  return 0;
}
// CHECK: KLEE: done: completed paths = 3
