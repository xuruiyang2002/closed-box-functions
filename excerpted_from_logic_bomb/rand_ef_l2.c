#include <string.h> 
#include "klee/klee.h"
#include "a_tester.h"

int logic_bomb(char* s) {
    int symvar = s[0];
    srand(symvar);
    int r = rand() % 100;
    if (r == 77) {
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
