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
  int y;
  klee_make_symbolic(&y, sizeof(y), "y");
  int symcrete_y  = abs(x);

  if (symcrete_x == 1) {
    printf("PATH 1: x is 1\n");
  } else {
    printf("PATH 2: x is not 1\n");
  }

  if (symcrete_y == 0) {    
    printf("PATH 3: y is 0\n");
  } else {
    printf("PATH 4: y is not 0\n");
  }

  return 0;
}
