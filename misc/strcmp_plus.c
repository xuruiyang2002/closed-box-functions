// RUN: %clang %s -emit-llvm -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --recolossus --search=bfs --max-fuzz-solver-time=120s --output-dir=%t.klee-out --external-calls=all %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// CHECK-DAG: strcmp
int main() {
  char str[3];
  klee_make_symbolic(str, sizeof(str), "array");
  str[1] = 'x';
  klee_assume(str[2] == '\0');
  int r = strcmp(str, "e");
  if (r != 0) {
    // CHECK-DAG: str is not 'e'
    printf("str is not 'e'\n");
  } else {
    // CHECK-DAG: str is 'e'
    printf("str is 'e'\n");
  }
  // CHECK-DAG: KLEE: done: completed paths = 2
  return 0;
}
