#include "klee/klee.h"
#include <stdio.h>
#include <string.h>
 
int main () {
  char str[] ="a-";
  const char deli;
 
  klee_make_symbolic(&deli, sizeof(deli), "deli");
  
  // CHECK-DAG: Yes
  // CHECK-DAG: No
  char *pch = strtok(str, &deli);
  if (*(pch + 1) == '\0') {
    // 'a', '\0'
    printf("Yes\n"); 
  } else  {
    // 'a', '-'
    printf("No\n");
  }
 
  // CHECK-DAG: KLEE: done: completed paths = 2  
 
  return 0;                                                                                                                             
} 
