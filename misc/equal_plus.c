// RUN: %clang %s -emit-llvm -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --recolossus --search=bfs --max-fuzz-solver-time=120s --output-dir=%t.klee-out --external-calls=all %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"
#include <stdio.h>
#include <stdlib.h>
// CHECK-DAG: abs
int main() {
  int x;
  klee_make_symbolic(&x, sizeof(x), "x");
  int symcrete_x = abs(x);
  
  if (symcrete_x == 0) {
      if (symcrete_x == 1) {
        printf("PATH 1: x is 1\n");
        klee_assert(0 && "Should not reach here");
      } else {
        printf("PATH 2: x is not 1\n");
      }
  }

  return 0;
}
