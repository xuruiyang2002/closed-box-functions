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
  
  if (1 > symcrete_x) {
    printf("PATH 1\n");
  } else {
    printf("PATH 2\n");
  }

  return 0;
}
