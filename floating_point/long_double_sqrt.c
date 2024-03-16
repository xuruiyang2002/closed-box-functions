#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

// Check if x is 9.xxx
int main() {
    long double x;
    klee_make_symbolic(&x, sizeof(x), "x");

    // CHECK-DAG: Yes
    // CHECK-DAG: No 
    long double root = klee_sqrt_long_double(x);
    long double tolerance = 1e-6;

    bool is_equal = klee_abs_long_double(root - 3) < tolerance;
    if (is_equal) {
        printf("Yes, the root is %Lf\n", root);
    } else {
        printf("No, the root is %Lf\n", root);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
