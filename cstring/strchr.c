#include "klee/klee.h"
#include <stdio.h>
#include <string.h>

int main () {
  char str[2];

  klee_make_symbolic(str, sizeof(str), "array");
  klee_assume(str[1] == '\0');

  // CHECK-DAG: Yes
  // CHECK-DAG: No
  char *p = (char*)strchr(str, 'e');
  if (p == str) {
    // str[0] is 'e'
    printf ("Yes\n");
  } else if (p == NULL) {
    // str[0] is not 'e'
    printf ("No\n");
  } else {
    klee_assert(0 && "sanity check");
  }

  // CHECK-DAG: KLEE: done: completed paths = 2

  return 0;
}
