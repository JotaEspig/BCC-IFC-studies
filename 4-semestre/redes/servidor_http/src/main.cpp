#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "server_tcp.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    ServerTCP server;
    server.bind();
    server.listen();
    Client client = server.accept_client();
    bool should_stop = false;
    char buffer[BUFLEN] = {0};
    server.send_to_client(client, "Hello from server!\n");

    std::mutex mtx;
    std::thread input_thread([&]() {
        std::string input;
        while (!should_stop) {
            std::getline(std::cin, input);
            if (input == "exit") {
                std::lock_guard<std::mutex> lock(mtx);
                should_stop = true;
                break;
            }
            input += "\n";
            server.send_to_client(client, input.c_str());
        }
    });

    while (true) {
        std::lock_guard<std::mutex> lock(mtx);
        if (should_stop) {
            break;
        }
        if (server.read_from_client(client, buffer) == 0) {
            std::cout << "Client disconnected" << std::endl;
            input_thread.join();
            return 0;
        }
        if (std::string(buffer) == "exit") {
            std::lock_guard<std::mutex> lock(mtx);
            should_stop = true;
            break;
        }
        std::cout << "Received: " << buffer << std::endl;
    }

    input_thread.join();
    server.close();

    return 0;
}
