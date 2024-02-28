#include "klee/klee.h"
#include<stdio.h>
#include <stdlib.h>

int main() {
    char str[2];

    klee_make_symbolic(str, sizeof(str), "array");
    klee_assume(str[1] == '\0');

    // CHECK-DAG: Yes
    // CHECK-DAG: No 
    float x = atof(str);
    x = x / -10000.0;
    if(1024 + x == 1024 && x > 0) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
