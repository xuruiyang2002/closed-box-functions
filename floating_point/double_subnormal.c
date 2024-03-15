#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    double a; // This could be subnormal
    klee_make_symbolic(&a, sizeof(a), "a");
    //
    bool is_subnormal = klee_is_subnormal_double(a);
	if (is_subnormal) {
        printf("Yes: the value of a is %lf\n", a);
    } else {
        printf("No: the value of a is %lf\n", a);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
