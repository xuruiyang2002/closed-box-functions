#include "klee/klee.h"
#include <stdio.h>
#include <string.h>

int main() {
  char str[2];

  klee_make_symbolic(str, sizeof(str), "array");
  klee_assume(str[1] == '\0');

  // CHECK-DAG: Equal
  // CHECK-DAG: Greater 
  // CHECK-DAG: Less 
  int r = strcoll(str, "e");
  if (r == 0) printf("Equal\n");
  else if (r > 0) printf("Greater\n");
  else printf("Less\n");

  // CHECK-DAG: KLEE: done: completed paths = 3
  
  return 0;
}

