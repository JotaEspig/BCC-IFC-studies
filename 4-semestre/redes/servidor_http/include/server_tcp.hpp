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
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

#include "defines.hpp"

/**
 * @brief ServerTCP class that abstracts the server side of a TCP connection.
 * Works on both Windows and Unix systems.
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class ServerTCP {
public:
    ServerTCP();

    void bind();
    void listen();
    Client accept_client();
    int read_from_client(Client client, char *buffer, int buffer_len = BUFLEN);
    void send_to_client(Client client, const char *message);
    void print_error();
    void close();
    void cleanup();

private:
#ifdef _WIN32
    SOCKET server_fd = INVALID_SOCKET;
    WSADATA wsaData;
#else
    int server_fd = INVALID_SOCKET;
#endif
    struct sockaddr_in address;
};
