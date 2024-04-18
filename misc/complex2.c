// RUN: %clang %s -emit-llvm -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --recolossus --search=bfs --max-fuzz-solver-time=120s --output-dir=%t.klee-out --external-calls=all %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"
#include <stdio.h>
#include <stdlib.h>
// CHECK-DAG: abs
int main() {
  int w;
  klee_make_symbolic(&w, sizeof(w), "w");
  int y = abs(w);
  int x = abs(y);

  if (x == 42) {
    printf("PATH: x = %d, y = %d, w = %d\n", x, y, w);
  }
  if (x == 84) {
    printf("PATH: x = %d, y = %d, w = %d\n", x, y, w);
  }

  return 0;
}
