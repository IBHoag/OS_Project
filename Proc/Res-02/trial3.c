#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 1024 * 1024;
    void *ptr = malloc(size);
    if (ptr == NULL) {
        return 1;
    }
    memset(ptr, 0xAA, size);
    free(ptr);
    return 0;
}
