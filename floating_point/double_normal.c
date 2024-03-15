#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    double a = 1.0;
    double b;
    klee_make_symbolic(&b, sizeof(b), "b");

    double c = a / b; // This could be normal
    bool is_normal = klee_is_normal_double(c);
	if (is_normal) {
        printf("Yes: the value of c is %lf\n", c);
    } else {
        printf("No: the value of c is %lf\n", c);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
