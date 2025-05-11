#include "socket_windows.h"

#include <winsock2.h>
#include <ws2tcpip.h>

WindowsSocket::WindowsSocket(SOCKET socket) : socket(socket) {}

WindowsSocket::~WindowsSocket() { close(); }

bool WindowsSocket::connect(const char* host, int port) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(host);

    if (::connect(socket,
                  reinterpret_cast<sockaddr*>(&serverAddr),
                  sizeof(serverAddr)) == SOCKET_ERROR) {
        close();
        return false;
    }

    return true;
}

int WindowsSocket::send(const char* data, int length) {
    return ::send(socket, data, length, 0);
}

int WindowsSocket::receive(char* buffer, int length) {
    return ::recv(socket, buffer, length, 0);
}

void WindowsSocket::close() {
    if (socket != INVALID_SOCKET) {
        closesocket(socket);
        socket = INVALID_SOCKET;
    }
}
