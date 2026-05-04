#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        exit(1);
    } else if (pid == 0) {
        exit(0);
    } else {
        sleep(5);
        wait(NULL);
    }

    return 0;
}
