#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // 1. Create Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Define Address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // 3. Bind and Listen
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    listen(server_fd, 3);
    printf("Server is listening on port 8080...\n");

    // 4. Accept a connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // 5. Read the request
    read(new_socket, buffer, 1024);
    printf("--- Request Received ---\n%s\n", buffer);

    // 6. Close the sockets (Good practice!
    close(new_socket);
    close(server_fd);

    return 0;
}
