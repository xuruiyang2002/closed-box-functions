#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    float a; // This could be subnormal
    klee_make_symbolic(&a, sizeof(a), "a");
    //
    bool is_subnormal = klee_is_subnormal_float(a);
	if (is_subnormal) {
        printf("Yes: the value of a is %f\n", a);
    } else {
        printf("No: the value of a is %f\n", a);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
