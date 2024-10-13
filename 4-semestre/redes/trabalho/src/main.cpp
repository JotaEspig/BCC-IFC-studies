#include <iostream>

#include "server_tcp.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    ServerTCP server;
    server.bind_socket();
    server.listen_socket();
    Client client = server.accept_client();
    server.send_to_client(client);
    char buffer[BUFLEN];
    server.read_from_client(client, buffer);
    std::cout << "Received: " << buffer << std::endl;
    server.close();
    server.cleanup();

    return 0;
}