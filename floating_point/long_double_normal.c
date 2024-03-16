#include "klee/klee.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    long double a = 1.0;
    int b;
    klee_make_symbolic(&b, sizeof(b), "b");

    long double c = a / b; // This could be normal
    bool is_normal = klee_is_normal_long_double(c);
	if (is_normal) {
        printf("Yes: the value of a is %Lf, b is %d, c is %Lf\n"
                        "(long double sometimes cannot be represented precisely due to the limitation of llvm execution engine)\n", a, b, c);
    } else {
        printf("No: the value of a is %Lf, b is %d, c is %Lf\n"
                        "(long double sometimes cannot be represented precisely due to the limitation of llvm execution engine)\n", a, b, c);
    }

    // CHECK-DAG: Two paths to explore, Yes and No.

    return 0; 
}
