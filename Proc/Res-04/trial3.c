#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>

int main() {
    setpriority(PRIO_PROCESS, 0, 10);

    double pi = 0.0;
    unsigned long long i;
    for (i = 0; ; i++) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
        pi += term;
    }

    return 0;
}
