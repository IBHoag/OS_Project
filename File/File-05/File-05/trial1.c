#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

int main() {
    const char *path = "lockfile.txt";
    const char *text = "Locked";
    
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) return 1;

    if (flock(fd, LOCK_EX) == 0) {
        write(fd, text, strlen(text));
        flock(fd, LOCK_UN);
    }

    close(fd);
    return 0;
}
