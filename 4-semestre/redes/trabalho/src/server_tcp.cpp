#include <exception>
#include <iostream>

#include "server_tcp.hpp"

ServerTCP::ServerTCP() {
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        int error_code = WSAGetLastError();
        std::cerr << "WSAStartup failed.\nError Code: " << error_code
                  << std::endl;
        throw std::runtime_error("WSAStartup failed");
    }
#endif
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
#ifdef _WIN32
        std::cerr << "Error code: " << WSAGetLastError() << std::endl;
#endif
        throw std::runtime_error("Socket creation failed");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(9090);
}

void ServerTCP::bind_socket() {
    if (bind(server_fd, (sockaddr *)&address, sizeof(address))
        == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
#ifdef _WIN32
        std::cerr << "Error code: " << WSAGetLastError() << std::endl;
#endif
        close();
        throw std::runtime_error("Bind failed");
    }
}

void ServerTCP::listen_socket() {
    if (listen(server_fd, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed" << std::endl;
#ifdef _WIN32
        std::cerr << "Error code: " << WSAGetLastError() << std::endl;
#endif
        close();
        throw std::runtime_error("Listen failed");
    }
}

Client ServerTCP::accept_client() {
    Client client;
    client = accept(server_fd, NULL, NULL);
    if (client == INVALID_SOCKET) {
        std::cerr << "Accept failed" << std::endl;
#ifdef _WIN32
        std::cerr << "Error code: " << WSAGetLastError() << std::endl;
#endif
        close();
        throw std::runtime_error("Accept failed");
    }
    return client;
}

void ServerTCP::read_from_client(Client client, char *buffer, int buffer_len) {
    int bytes_received = recv(client, buffer, buffer_len, 0);
    if (bytes_received == SOCKET_ERROR) {
        std::cerr << "Receive failed" << std::endl;
#ifdef _WIN32
        std::cerr << "Error code: " << WSAGetLastError() << std::endl;
#endif
        close();
        throw std::runtime_error("Receive failed");
    }
    buffer[bytes_received] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';
}

void ServerTCP::send_to_client(Client client) {
    const char *message = "Hello from server";
    int bytes_sent = send(client, message, strlen(message), 0);
    if (bytes_sent == SOCKET_ERROR) {
        std::cerr << "Send failed" << std::endl;
#ifdef _WIN32
        std::cerr << "Error code: " << WSAGetLastError() << std::endl;
#endif
        close();
        throw std::runtime_error("Send failed");
    }
}

void ServerTCP::close() {
#ifdef _WIN32
    closesocket(server_fd);
    cleanup();
#else
    close(server_fd);
#endif
}

void ServerTCP::cleanup() {
#ifdef _WIN32
    WSACleanup();
#endif
}
