#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    int x;

    klee_make_symbolic(&x, sizeof(int), "x");

    // CHECK-DAG: Yes
    // CHECK-DAG: No 
    double a = x * 70.0;
    double b = 140.0;
    double tolerance = 1e-6;

    bool is_equal = klee_abs_double(a - b) < tolerance ;
	if(is_equal) {
        printf("Yes: the value of a is %lf\n", a);
    } else {
        printf("No: the value of a is %lf\n", a);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
