#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/wait.h>

struct shared_data {
    sem_t empty;
    sem_t full;
    int buffer;
};

int main() {
    struct shared_data *shared = mmap(NULL, sizeof(struct shared_data),
                                     PROT_READ | PROT_WRITE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(&shared->empty, 1, 1);
    sem_init(&shared->full, 1, 0);

    pid_t pid = fork();

    if (pid == 0) {
        sem_wait(&shared->full);
        printf("%d\n", shared->buffer);
        sem_post(&shared->empty);
        exit(0);
    } else {
        int val = 42;
        sem_wait(&shared->empty);
        shared->buffer = val;
        sem_post(&shared->full);
        wait(NULL);
    }

    sem_destroy(&shared->empty);
    sem_destroy(&shared->full);
    munmap(shared, sizeof(struct shared_data));

    return 0;
}
