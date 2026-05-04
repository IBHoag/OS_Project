#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void handle_sigusr1(int sig) {
    write(STDOUT_FILENO, "Received\n", 9);
}

int main() {
    pid_t pid;
    struct sigaction sa;

    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        while (1) {
            pause();
        }
    } else {
        sleep(1);
        kill(pid, SIGUSR1);
        sleep(1);
    }

    return 0;
}
