#include "klee/klee.h"
#include<stdio.h>
#include <stdlib.h>

int main() {
    int x;

    klee_make_symbolic(&x, sizeof(int), "x");

    // The reason why I don’t want to use epsilon (a small threshold)
    // is that I don’t want to introduce more function calls, 
    // that is, the fabs function.

    // CHECK-DAG: Yes
    // CHECK-DAG: No 
    float y = x + 0.0000005;
    if (y != 7) {
        float y = x + 1;
        if(y == 8) {
            printf("Yes\n");
        }
    } else {
        printf("No\n");
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}

