#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
    const char *name = "/shm_example";
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(int));
    int *shared_int = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    *shared_int = 10;

    pid_t pid = fork();

    if (pid == 0) {
        *shared_int = 42;
        munmap(shared_int, sizeof(int));
        exit(0);
    } else {
        wait(NULL);
        printf("%d\n", *shared_int);
        munmap(shared_int, sizeof(int));
        close(shm_fd);
        shm_unlink(name);
    }

    return 0;
}
