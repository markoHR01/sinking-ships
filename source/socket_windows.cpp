#include "socket_windows.h"
#include "constants.h"

#include <winsock2.h>
#include <ws2tcpip.h>

WindowsSocket::WindowsSocket(SOCKET socket) : socket(socket) {}

WindowsSocket::~WindowsSocket() { close(); }

bool WindowsSocket::connect(const char* host, int port) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &serverAddr.sin_addr) != 1) {
        return false;
    }

    if (::connect(socket,
                  reinterpret_cast<sockaddr*>(&serverAddr),
                  sizeof(serverAddr)) == SOCKET_ERROR) {
        close();
        return false;
    }

    return true;
}

int WindowsSocket::send(const char* data, int length) {
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(socket, &writefds);

    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = SOCKET_SELECT_TIMEOUT * 1000;

    int result = select(0, nullptr, &writefds, nullptr, &timeout);

    if (result > 0 && FD_ISSET(socket, &writefds)) {
        return ::send(socket, data, length, 0);
    } else if (result == 0) {
        return 0;
    } else {
        return -1;
    }
}

int WindowsSocket::receive(char* buffer, int length) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(socket, &readfds);

    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = SOCKET_SELECT_TIMEOUT * 1000;

    int result = select(0, &readfds, nullptr, nullptr, &timeout);

    if (result > 0 && FD_ISSET(socket, &readfds)) {
        return ::recv(socket, buffer, length, 0);
    } else if (result == 0) {
        return 0;
    } else {
        return -1;
    }
}

void WindowsSocket::close() {
    if (socket != INVALID_SOCKET) {
        closesocket(socket);
        socket = INVALID_SOCKET;
    }
}
