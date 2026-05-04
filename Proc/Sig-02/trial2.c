#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig) {
    write(STDOUT_FILENO, "Received\n", 9);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        return 1;
    } else if (pid == 0) {
        struct sigaction sa;
        sa.sa_handler = handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGUSR1, &sa, NULL);

        while (1) {
            pause();
            _exit(0);
        }
    } else {
        sleep(1);
        kill(pid, SIGUSR1);
        wait(NULL);
    }

    return 0;
}
