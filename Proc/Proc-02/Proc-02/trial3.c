#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            exit(1);
        } else if (pid == 0) {
            sleep(2);
            exit(0);
        }
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}
