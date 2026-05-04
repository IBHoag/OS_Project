#include <stdlib.h>
#include <string.h>

int main() {
    void *ptr = malloc(1024 * 1024);
    if (ptr == NULL) {
        return 1;
    }
    memset(ptr, 0xAA, 1024 * 1024);
    free(ptr);
    return 0;
}
