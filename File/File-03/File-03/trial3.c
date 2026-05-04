#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) return 1;

    struct stat st;
    if (fstat(fd, &st) == -1) {
        close(fd);
        return 1;
    }

    size_t size = st.st_size;
    if (size == 0) {
        close(fd);
        return 0;
    }

    char *addr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        close(fd);
        return 1;
    }

    for (ssize_t i = size - 1; i >= 0; i--) {
        putchar(addr[i]);
    }

    munmap(addr, size);
    close(fd);
    return 0;
}
