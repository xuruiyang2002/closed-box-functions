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

  if (y > 1) {
      if (symcrete_x > y) {
          if (symcrete_x == 0) {
            klee_assert(0 && "Should not reach here");
          } else {
            printf("PATH 1");
          }
      } else {
        printf("PATH 2\n");
      }
  } else {
    printf("PATH 3\n");
  }
  return 0;
}
