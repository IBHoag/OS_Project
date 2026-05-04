#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    const char *name = "/shm_example";
    const int size = sizeof(int);

    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, size);

    int *ptr = (int *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    *ptr = 100;

    pid_t pid = fork();

    if (pid == 0) {
        *ptr = 200;
        exit(0);
    } else {
        wait(NULL);
        printf("%d\n", *ptr);
        
        munmap(ptr, size);
        close(shm_fd);
        shm_unlink(name);
    }

    return 0;
}
