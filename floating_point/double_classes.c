#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    double a;
    klee_make_symbolic(&a, sizeof(a), "a");

    bool is_normal    = klee_is_normal_double(a);
    bool is_subnormal = klee_is_subnormal_double(a);
    bool is_inf       = klee_is_infinite_double(a);
    bool is_nan       = klee_is_nan_double(a);

	if (is_normal) {
	    printf("Normal: the value of a is: %lf\n", a);
    }
	if (is_subnormal) {
	    printf("Subnormal: the value of a is: %lf\n", a);
    }
	if (is_inf) {
	    printf("Infinite: the value of a is: %lf\n", a);
    }
	if (is_nan) {
	    printf("NaN: the value of a is: %lf\n", a);
    }

    // CHECK-DAG: Four paths to explore,
    //  normal, subnormal, infinite, nan 

    return 0; 
}
