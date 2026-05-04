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
        struct sigaction sa;
        sa.sa_handler = handle_sigusr1;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGUSR1, &sa, NULL);

        while (1) {
            pause();
        }
    } else {
        sleep(1);
        kill(pid, SIGUSR1);
        waitpid(pid, NULL, 0);
    }

    return 0;
}
