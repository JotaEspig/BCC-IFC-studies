#pragma once

#ifdef _WIN32
#include <conio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define Client SOCKET
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define Client int
#endif

#include "defines.hpp"

class ServerTCP {
public:
    ServerTCP();

    void bind_socket();
    void listen_socket();
    Client accept_client();
    void read_from_client(Client client, char *buffer, int buffer_len = BUFLEN);
    void send_to_client(Client client);
    void close();
    void cleanup();

private:
#ifdef _WIN32
    SOCKET server_fd = INVALID_SOCKET;
    WSADATA wsaData;
#else
    int server_fd = 0;
#endif
    struct sockaddr_in address;
};