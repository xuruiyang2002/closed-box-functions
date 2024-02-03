#include "klee/klee.h"
#include <stdio.h>
#include <string.h>

int main () {
  char str[2];

  klee_make_symbolic(str, sizeof(str), "str");
  klee_assume(str[1] == '\0');

  // CHECK-DAG: Yes
  // CHECK-DAG: No
  char *p = strstr(str, "e");
  if (p == str) {
    printf("Yes\n");
  } else if (p == NULL){
    printf("No\n");
  } else {
    klee_assert(0 && "sanity check");
  }

  // CHECK-DAG: KLEE: done: completed paths = 2

  return 0;
}
