#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    int x;

    klee_make_symbolic(&x, sizeof(int), "x");

    // CHECK-DAG: Yes
    // CHECK-DAG: No 
    float y = x + 0.0000005;
    float tolerance = 1e-6;

    bool is_equal = klee_abs_float(y - 7) < tolerance;
    if (is_equal) {
        printf("Yes: the value of y is %f\n", y);
    } else {
        printf("No: the value of y is %f\n", y);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}

