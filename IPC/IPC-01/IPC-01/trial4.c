#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[16];
    const char *msg = "Hello OS";

    if (pipe(pipefd) == -1) {
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        return 1;
    }

    if (pid > 0) {
        close(pipefd[0]);
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);
    } else {
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        close(pipefd[0]);
    }

    return 0;
}
