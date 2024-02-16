#include "klee/klee.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char str[2];

    klee_make_symbolic(str, sizeof(str), "array");
    klee_assume(str[1] == '\0');

    // CHECK-DAG: Yes
    // CHECK-DAG: No
    int symvar = str[0] - 48;
    int pid = (int) getpid();
    if (pid % 78 == symvar) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    // CHECK-DAG: KLEE: done: completed paths = 2

    return 0;
}