#include "socket_unix.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

UnixSocket::UnixSocket(int socket) : socket(socket) {}

UnixSocket::~UnixSocket() { close(); }

bool UnixSocket::connect(const char* host, int port) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &serverAddr.sin_addr) != 1) {
        return false;
    }

    if (::connect(socket,
                  reinterpret_cast<sockaddr*>(&serverAddr),
                  sizeof(serverAddr)) < 0) {
        close();
        return false;
    }

    return true;
}

int UnixSocket::send(const char* data, int length) {
    return ::send(socket, data, length, 0);
}

int UnixSocket::receive(char* buffer, int length) {
    return ::recv(socket, buffer, length, 0);
}

void UnixSocket::close() {
    if (socket >= 0) {
        ::close(socket);
        socket = -1;
    }
}
