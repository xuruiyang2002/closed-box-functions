#include <string.h> 
#include <math.h>
#include "klee/klee.h"
#include "a_tester.h"

#define PI 3.14159265358979323846264338327


int logic_bomb(char* s) {
    int symvar = s[0];
    float v = sin(symvar * PI / 30);
    if (v > 0.5) {
        return BOMB_ENDING;
    } else {
        return NORMAL_ENDING;
    }
}

int main() {
    char str[2];

    klee_make_symbolic(str, sizeof(str), "array");
    klee_assume(str[1] == '\0');

    // CHECK-DAG: BOMB
    // CHECK-DAG: NORMAL
    int r = logic_bomb(str);
    if (r == BOMB_ENDING) {
        printf("BOMB\n");
    } else {
        printf("NORNAL\n");
    }

    // CHECK-DAG: KLEE: done: completed paths = 2

    return 0;
}
