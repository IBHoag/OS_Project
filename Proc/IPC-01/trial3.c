#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char buffer[16];

    if (pipe(fd) == -1) {
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        return 1;
    }

    if (pid > 0) {
        close(fd[0]);
        write(fd[1], "Hello OS", 9);
        close(fd[1]);
    } else {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        close(fd[0]);
    }

    return 0;
}
