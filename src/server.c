#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include "common.h"

#define BUFF_SIZE 1024
#define LISTEN_BACKLOG 5

int main(int argc, char **argv) {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("socket error");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(13);

    if (bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind error");
        return 1;
    }

    if (listen(listen_fd, LISTEN_BACKLOG) < 0) {
        perror("listen error");
        return 1;
    }

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int conn_fd = accept(listen_fd, (struct sockaddr *) &client_addr, &client_len);

        char buff[BUFF_SIZE];
        printf("connection from %s, port %d\n", inet_ntop(AF_INET, &client_addr.sin_addr, buff, sizeof(buff)), ntohs(client_addr.sin_port));
        time_t ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(conn_fd, buff, strlen(buff));

        close(conn_fd);
    }
}
