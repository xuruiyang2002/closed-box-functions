#include "klee/klee.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char str[2];
    int result;

    klee_make_symbolic(str, sizeof(str), "array");
    klee_assume(str[1] == '\0');

    int symvar = str[0] - 48;
    char file[] = "tmp.syscall";
    int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC);
    if (fd < 0) {
        exit(-1);
    }

    // CHECK-DAG: Yes
    // CHECK-DAG: No
    write(fd, &symvar, sizeof(symvar));
    close(fd);
    fd = open(file, O_RDONLY);
    read(fd, &result, sizeof(result));
    close(fd);

    if(result == 7) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    // CHECK-DAG: KLEE: done: completed paths = 2

    return 0;
}