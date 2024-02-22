#include "klee/klee.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
  int errnum;

  klee_make_symbolic(&errnum, sizeof(errnum), "errnum");

  // CHECK-DAG: Yes
  // CHECK-DAG: No
  char *msg = strerror(errnum);
  if (msg[0] == 'N') {
    // i.e. No such file or directory
    printf ("Yes\n");
  } else {
    printf ("No\n");
  }

  // CHECK-DAG: KLEE: done: completed paths = 2

  return 0;
}
