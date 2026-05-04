#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_sigchld(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
    write(STDOUT_FILENO, "Child exited\n", 13);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = &handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        sleep(2);
        _exit(0);
    } else {
        while (1) {
            pause();
        }
    }

    return 0;
}
