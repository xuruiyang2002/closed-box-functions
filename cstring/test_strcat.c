#include "klee/klee.h"
#include <stdio.h>
#include <string.h>

int main() {
  char str[2];

  klee_make_symbolic(str, sizeof(str), "array");
  klee_assume(str[1] == '\0');

  // CHECK-DAG: Yes
  // CHECK-DAG: No 
  char *p = strcat(str, "\0");
  if (p == str) {
    printf("Yes\n");
  } else {
    klee_assert(0 && "sanity check");
  }

  // CHECK-DAG: KLEE: done: completed paths = 1
  
  return 0;
}
