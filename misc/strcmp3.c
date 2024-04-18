// RUN: %clang %s -emit-llvm -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --recolossus --search=bfs --max-fuzz-solver-time=120s --output-dir=%t.klee-out --external-calls=all %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char str[2];
  klee_make_symbolic(str, sizeof(str), "str");
  klee_assume(str[1] == '\0');

  char *ptr;
  klee_make_symbolic(&ptr, sizeof(ptr), "ptr");

  int r = strcmp(str, "e");
  if (ptr == str) {
      if (r != 0) { // <--- Q2
        printf("str is not 'e'\n");
      } else {      // <--- Q2
        printf("str is 'e'\n");
      }   
  }

  return 0;
}
