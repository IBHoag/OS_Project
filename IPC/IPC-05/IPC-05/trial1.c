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
    struct shared_data *data = mmap(NULL, sizeof(struct shared_data),
                                   PROT_READ | PROT_WRITE,
                                   MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(&data->empty, 1, 1);
    sem_init(&data->full, 1, 0);

    pid_t pid = fork();

    if (pid == 0) {
        sem_wait(&data->full);
        printf("%d\n", data->buffer);
        sem_post(&data->empty);
        exit(0);
    } else {
        sem_wait(&data->empty);
        data->buffer = 42;
        sem_post(&data->full);
        wait(NULL);
    }

    sem_destroy(&data->empty);
    sem_destroy(&data->full);
    munmap(data, sizeof(struct shared_data));

    return 0;
}
