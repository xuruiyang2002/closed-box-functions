#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

// Check if x is 9.xxx
int main() {
    double x;
    klee_make_symbolic(&x, sizeof(x), "x");

    // CHECK-DAG: Yes
    // CHECK-DAG: No 
    double root = klee_sqrt_double(x);
    double tolerance = 1e-6;

    bool is_equal = klee_abs_double(root - 3) < tolerance;
    if (is_equal) {
        printf("Yes, the root is %lf\n", root);
    } else {
        printf("No, the root is %lf\n", root);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
