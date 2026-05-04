#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

struct shared_data {
    sem_t empty;
    sem_t full;
    int buffer;
};

int main() {
    struct shared_data *shm = mmap(NULL, sizeof(struct shared_data),
                                   PROT_READ | PROT_WRITE,
                                   MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(&shm->empty, 1, 1);
    sem_init(&shm->full, 1, 0);

    pid_t pid = fork();

    if (pid == 0) {
        sem_wait(&shm->full);
        printf("%d\n", shm->buffer);
        sem_post(&shm->empty);
        exit(0);
    } else {
        sem_wait(&shm->empty);
        shm->buffer = 42;
        sem_post(&shm->full);
        wait(NULL);
    }

    sem_destroy(&shm->empty);
    sem_destroy(&shm->full);
    munmap(shm, sizeof(struct shared_data));

    return 0;
}
