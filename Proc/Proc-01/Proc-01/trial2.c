#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        return 1;
    } else if (pid == 0) {
        printf("%d\n", getpid());
        exit(0);
    } else {
        wait(NULL);
        printf("Child done\n");
    }

    return 0;
}
