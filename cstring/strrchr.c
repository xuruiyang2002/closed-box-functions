#include "klee/klee.h"
#include <stdio.h>
#include <string.h>

int main () {
  char str[2] = "e";
  int ch;

  klee_make_symbolic(&ch, sizeof(ch), "ch");

  // CHECK-DAG: Yes
  // CHECK-DAG: No 
  char *p = strrchr(str, ch);
  if (p == str) {
    // str[0] is 'e'
    printf("Yes\n"); 
  } else if (p == NULL){
    // str[0] is not 'e'
    printf("No\n"); 
  } else {
    klee_assert(0 && "sanity check");
  }

  // CHECK-DAG: KLEE: done: completed paths = 2

  return 0;
}
