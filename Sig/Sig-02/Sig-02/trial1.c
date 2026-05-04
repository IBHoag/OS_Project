#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_sigusr1(int sig) {
    write(STDOUT_FILENO, "Received\n", 9);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        return 1;
    }

    if (pid == 0) {
        struct sigaction sa = {0};
        sa.sa_handler = handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);

        while (1) {
            pause();
            break;
        }
        exit(0);
    } else {
        sleep(1);
        kill(pid, SIGUSR1);
        wait(NULL);
    }

    return 0;
}
