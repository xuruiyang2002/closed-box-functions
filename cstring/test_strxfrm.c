#include "klee/klee.h"
#include <stdio.h>
#include <string.h>

int main() {
  char str[2];

  klee_make_symbolic(str, sizeof(str), "array");
  klee_assume(str[1] == '\0');

  // CHECK-DAG: Zero
  // CHECK-DAG: One 
  int r = strxfrm(NULL, str, 0); // retrieve the length
  if (r == 0) printf("Zero\n");
  else if (r == 1) printf("One\n");
  else klee_assert(0 && "sanity check\n");

  // CHECK-DAG: KLEE: done: completed paths = 2
  
  return 0;
}
