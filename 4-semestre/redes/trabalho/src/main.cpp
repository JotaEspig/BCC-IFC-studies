#include <iostream>
#include <string>
#include <thread>

#include "server_tcp.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    ServerTCP server;
    server.bind_socket();
    server.listen_socket();
    Client client = server.accept_client();
    bool should_stop = false;
    char buffer[BUFLEN] = {0};
    server.send_to_client(client, "Hello from server!\n");
    std::thread input_thread([&]() {
        std::string input;
        while (!should_stop) {
            std::getline(std::cin, input);
            if (input == "exit") {
                should_stop = true;
                break;
            }
            input += "\n";
            server.send_to_client(client, input.c_str());
        }
    });

    while (!should_stop) {
        server.read_from_client(client, buffer);
        if (std::string(buffer) == "exit") {
            should_stop = true;
            break;
        }
        std::cout << "Received: " << buffer << std::endl;
    }

    input_thread.join();
    server.close();

    return 0;
}