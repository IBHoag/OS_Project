#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    pid_t pid = fork();

    if (pid == 0) {
        close(server_fd);
        int sock = 0;
        struct sockaddr_in serv_addr;
        char *message = "Test";

        sock = socket(AF_INET, SOCK_STREAM, 0);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(8080);
        inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

        while (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            usleep(10000);
        }

        send(sock, message, strlen(message), 0);
        close(sock);
        exit(0);
    } else {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        read(client_fd, buffer, 1024);
        printf("%s\n", buffer);
        close(client_fd);
        close(server_fd);
        wait(NULL);
    }

    return 0;
}
