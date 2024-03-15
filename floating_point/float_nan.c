#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    float a = 0.0;
    float b;
    klee_make_symbolic(&b, sizeof(b), "b");

    float c = a / b; // This may be NaN
    bool is_nan = klee_is_nan_float(c);
	if (is_nan) {
        printf("Yes: the value of c is %f\n", c);
    } else {
        printf("No: the value of c is %f\n", c);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
