#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    int x;

    klee_make_symbolic(&x, sizeof(int), "x");

    // CHECK-DAG: Yes
    // CHECK-DAG: No 
    float a = x / 70.0;
    float b = 0.1;
    float tolerance = 1e-6;

    bool is_equal = klee_abs_float(a - b) < tolerance ;
	if(is_equal) {
        printf("Yes: the value of a is %f\n", a);
    } else {
        printf("No: the value of a is %f\n", a);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
