#include "klee/klee.h"
#include <stdio.h>
#include <string.h>

int main () {
  char src[2], dest[2];

  klee_make_symbolic(src, sizeof(src), "array");
  klee_assume(src[1] == '\0');

  // CHECK-DAG: Yes
  // CHECK-DAG: No
  strncpy(dest, src, sizeof(src));
  if (dest[0] == 'e') {
    // str[0] is 'e'
    printf ("Yes\n");
  } else {
    // str[0] is not 'e'
    printf ("No\n");
  }

  // CHECK-DAG: KLEE: done: completed paths = 2

  return 0;
}
