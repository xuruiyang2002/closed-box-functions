#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    int x;

    klee_make_symbolic(&x, sizeof(int), "x");

    // CHECK-DAG: Yes
    // CHECK-DAG: No 
    long double a = x * 70.0;
    long double b = 140.0;
    long double tolerance = 1e-6;

    bool is_equal = klee_abs_long_double(a - b) < tolerance ;
	if(is_equal) {
        printf("Yes: the value of x is %d, a is %Lf, b is %Lf\n", x, a, b);
    } else {
        printf("No: the value of x is %d, a is %Lf, b is %Lf\n", x, a, b);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
