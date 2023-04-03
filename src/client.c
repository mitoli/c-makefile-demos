#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_LINE 1024

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("usage: client <IPAddress>");
        return 1;
    }

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket error");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13);

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("inet_pton error");
        return 1;
    }

    if (connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("connect error");
        return 1;
    }

    ssize_t n;
    char receive_line[MAX_LINE + 1];
    while ((n = read(sock_fd, receive_line, MAX_LINE)) > 0) {
        receive_line[n] = 0;
        if (fputs(receive_line, stdout) == EOF) {
            perror("fputs error");
            return 1;
        }
    }
    if (n < 0) {
        perror("read error");
        return 1;
    }

    return 0;
}
