// RUN: %clang %s -emit-llvm -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --recolossus --search=bfs --max-fuzz-solver-time=120s --output-dir=%t.klee-out --external-calls=all %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// CHECK-DAG: strcmp
int main() {
  char str[2];
  klee_make_symbolic(str, sizeof(str), "str");
  klee_assume(str[1] == '\0');

  char str2[2];
  klee_make_symbolic(str2, sizeof(str2), "str2");
  klee_assume(str2[1] == '\0');

  int r = strcmp(str, "e");
  int r2 = strcmp(str2, "q");
  if (r != 0) {
    // CHECK-DAG: str is not 'e'
    printf("str is not 'e'\n");
  } else {
    // CHECK-DAG: str is 'e'
    printf("str is 'e'\n");
  }

  if (r2 != 0) {
    // CHECK-DAG: str is not 'e'
    printf("str2 is not 'q'\n");
  } else {
    // CHECK-DAG: str is 'e'
    printf("str2 is 'q'\n");
  }
  // CHECK-DAG: KLEE: done: completed paths = 2
  return 0;
}
