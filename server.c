#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Define Address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind and Listen
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    listen(server_fd, 3);
    printf("Server is listening on port 8080...\n");

    while(1){
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        // Read the request
        read(new_socket, buffer, 1024);
        printf("--- Request Received ---\n%s\n", buffer);

        // Send response
        char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
        write(new_socket, hello, strlen(hello));
        memset(buffer, 0, sizeof(buffer));

        // Close client socket
        close(new_socket);
    }

    // Close main listener socket
    close(server_fd);

    return 0;
}
