#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        char *args[] = {"ls", NULL};
        execvp(args[0], args);
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }

    return 0;
}
