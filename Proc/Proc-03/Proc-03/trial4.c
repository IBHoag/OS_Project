#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        return 1;
    } else if (pid == 0) {
        char *args[] = {"ls", NULL};
        execvp(args[0], args);
        exit(1);
    } else {
        wait(NULL);
    }

    return 0;
}
