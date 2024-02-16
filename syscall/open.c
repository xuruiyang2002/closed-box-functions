#include "klee/klee.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char str[2];

    klee_make_symbolic(str, sizeof(str), "array");
    klee_assume(str[1] == '\0');

    int symvar = str[0] - 48;
    char file[] = "tmp.syscall";
    int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC);

    // CHECK-DAG: Yes
    // CHECK-DAG: No
    if(fd % 3 == symvar) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    // CHECK-DAG: KLEE: done: completed paths = 2

    return 0;
}