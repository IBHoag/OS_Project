#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>

int main() {
    setpriority(PRIO_PROCESS, 0, 10);

    volatile double x = 0;
    while (1) {
        for (long i = 1; i < 100000000; i++) {
            x += 1.0 / i;
        }
    }

    return 0;
}
