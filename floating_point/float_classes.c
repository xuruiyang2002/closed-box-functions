#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    float a;
    klee_make_symbolic(&a, sizeof(a), "a");

    bool is_normal    = klee_is_normal_float(a);
    bool is_subnormal = klee_is_subnormal_float(a);
    bool is_inf       = klee_is_infinite_float(a);
    bool is_nan       = klee_is_nan_float(a);

	if (is_normal) {
	    printf("Normal: the value of a is: %f\n", a);
    }
	if (is_subnormal) {
	    printf("Subnormal: the value of a is: %f\n", a);
    }
	if (is_inf) {
	    printf("Infinite: the value of a is: %f\n", a);
    }
	if (is_nan) {
	    printf("NaN: the value of a is: %f\n", a);
    }

    // CHECK-DAG: Four paths to explore,
    //  normal, subnormal, infinite, nan 

    return 0; 
}
