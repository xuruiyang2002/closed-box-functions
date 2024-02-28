#include<stdio.h>
#include <stdlib.h>
#include "a_tester.h"

int main() {
    char str[2];

    klee_make_symbolic(str, sizeof(str), "array");
    klee_assume(str[1] == '\0');

    // CHECK-DAG: Yes
    // CHECK-DAG: No 
    float x = atof(str);
    x = x / 10.0;
    x = x + 0.1;
    x = x * x;
    if (x > 0.1) {
        x -= x;
    }
    if(x != 0.02) {
        x = x + 7.98;
        if(x == 8) {
            printf("Yes\n");
        }
    } else {
        printf("No\n");
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0;
}
