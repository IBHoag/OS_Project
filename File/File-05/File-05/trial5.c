#include <stdio.h>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("lockfile.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) return 1;

    if (flock(fd, LOCK_EX) == 0) {
        write(fd, "Locked", 6);
        flock(fd, LOCK_UN);
    }

    close(fd);
    return 0;
}
