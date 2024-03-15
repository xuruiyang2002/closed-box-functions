#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    float a = 1.0;
    float b;
    klee_make_symbolic(&b, sizeof(b), "b");

    float c = a / b; // This may be INFINITY
    bool is_inf = klee_is_infinite_float(c);
	if (is_inf) {
        printf("Yes: the value of c is %f\n", c);
    } else {
        printf("Yes: the value of c is %f\n", c);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
