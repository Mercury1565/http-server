# http-server
A Socket: an endpoint for communication that allows my program to send and receive data over a network.

Since we are building a server, your program has to follow a specific "handshake" with the Operating System to start listening for visitors. Here is a high-level overview of the first few steps:
1. Create a Socket: Tell the OS you want a communication endpoint.
2. Bind: Assign a specific port (like 8080) to that socket.
3. Listen: Put the socket in a state where it's waiting for incoming connections.
4. Accept: Pick up the "phone" when someone calls.

## Create a Socket
In C, we use a function called socket(). It usually looks something like this:
```c
int server_fd = socket(AF_INET, SOCK_STREAM, 0);
```
- `AF_INET` specifically tells the system you are using IPv4 (the classic 192.168.x.x style addresses). If you wanted to support IPv6, you would use `AF_INET6`
- `SOCK_STREAM`, defines how the data is sent. In networking, there are two main ways to move data:
  - Streams (SOCK_STREAM): Think of this like a phone call. It creates a dedicated connection where data is guaranteed to arrive in the exact order it was sent (this uses the TCP protocol).
  - Datagrams (SOCK_DGRAM): Think of this like throwing paper airplanee. You toss the data out there; it's faster, but there's no guarantee it arrives or stays in order (this uses the UDP protocol).
- `0`,Let the OS choose the default protocol for this domain + type

## Giving the server an "Address"
```c
struct sockaddr_in address;
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY; // Listen on any available network interface
address.sin_port = htons(8080);      // Set the port to 8080
```

Here, we are defining the address structure for our server. The `sin_family` field specifies the address family (AF_INET for IPv4), `sin_addr.s_addr` sets the IP address to listen on (INADDR_ANY means all available interfaces), and `sin_port` sets the port number to 8080. The `htons()` function is used to convert the port number to network byte order.

Why the `htons()` function is used:
The `htons()` function is used to convert the port number to network byte order. This is necessary because the port number is represented as a 16-bit unsigned integer, and the byte order of this integer can vary depending on the system architecture(big-endian or little-endian). The `htons()` function ensures that the port number is represented in network byte order, which is required for communication over the network.

## Bind, Listen, Accept

1. Bind
```c
bind(server_fd, (struct sockaddr *)&address, sizeof(address));
```

2. Listen
```c
listen(server_fd, 3); // Allow a queue of 3 pending connections
```

3. Accept
```c
int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen); // accept wakes up and returns a new socket specifically for a visitor.
```

4. Read Request
```c
char buffer[1024] = {0};
read(new_socket, buffer, 1024);
printf("%s\n", buffer);
```
