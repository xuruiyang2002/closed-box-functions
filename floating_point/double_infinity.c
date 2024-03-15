#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    double a = 1.0;
    double b;
    klee_make_symbolic(&b, sizeof(b), "b");

    double c = a / b; // This may be INFINITY
    bool is_inf = klee_is_infinite_double(c);
	if (is_inf) {
        printf("Yes: the value of c is %lf\n", c);
    } else {
        printf("Yes: the value of c is %lf\n", c);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
