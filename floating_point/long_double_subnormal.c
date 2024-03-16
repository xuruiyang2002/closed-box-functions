#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    double a; // This could be subnormal
    klee_make_symbolic(&a, sizeof(a), "a");

    long double b = 1.0 / a;
    bool is_subnormal = klee_is_subnormal_long_double(b);
	if (is_subnormal) {
        printf("Yes: the value of a is %lf, b is %Lf\n"
                        "(long double sometimes cannot be represented precisely due to the limitation of llvm execution engine)\n", a, b);
    } else {
        printf("Yes: the value of a is %lf, b is %Lf\n"
                        "(long double sometimes cannot be represented precisely due to the limitation of llvm execution engine)\n", a, b);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
