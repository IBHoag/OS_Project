#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t keep_running = 1;

void handle_sigterm(int sig) {
    keep_running = 0;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigterm;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGTERM, &sa, NULL);

    while (keep_running) {
        sleep(1);
    }

    return 0;
}
