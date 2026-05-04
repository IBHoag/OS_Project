#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *path = "test.txt";
    const char *content = "Secure";
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        write(fd, content, 6);
        close(fd);
    }
    return 0;
}
