#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

// Check if x is 9.xxx
int main() {
    float x;
    klee_make_symbolic(&x, sizeof(x), "x");

    // CHECK-DAG: Yes
    // CHECK-DAG: No 
    float root = klee_sqrt_float(x);
    float tolerance = 1e-6;

    bool is_equal = klee_abs_float(root - 3) < tolerance;
    if (is_equal) {
        printf("Yes, the root is %f\n", root);
    } else {
        printf("No, the root is %f\n", root);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
