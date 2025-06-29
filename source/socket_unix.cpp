#include "socket_unix.h"
#include "constants.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#include <cstdio>
#include <cerrno>

UnixSocket::UnixSocket(int socket) : socket(socket) {}

UnixSocket::~UnixSocket() { close(); }

bool UnixSocket::connect(const char* host, int port) {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &serverAddr.sin_addr) != 1) {
        return false;
    }

    int status = ::connect(socket,
                           reinterpret_cast<sockaddr*>(&serverAddr),
                           sizeof(serverAddr));

    if (status == 0) return true;

    if (errno != EINPROGRESS) {
        close();
        return false;
    }

    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(socket, &writefds);

    timeval timeout{};
    timeout.tv_sec = 0;
    timeout.tv_usec = CONNECT_TIMEOUT * 1000;

    int result = select(socket + 1, nullptr, &writefds, nullptr, &timeout);

    if (result <= 0 || !FD_ISSET(socket, &writefds)) {
        close();
        return false;
    }

    int so_error = 0;
    socklen_t len = sizeof(so_error);
    if (getsockopt(socket,
                   SOL_SOCKET,
                   SO_ERROR,
                   &so_error,
                   &len) != 0 || so_error != 0) {
        close();
        return false;
    }

    return true;
}

int UnixSocket::send(const char* data, int length) {
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(socket, &writefds);

    timeval timeout{};
    timeout.tv_sec = 0;
    timeout.tv_usec = SOCKET_SELECT_TIMEOUT * 1000;

    int result = select(socket + 1, nullptr, &writefds, nullptr, &timeout);

    if (result > 0 && FD_ISSET(socket, &writefds)) {
        return ::send(socket, data, length, 0);
    } else if (result == 0) {
        return 0;
    } else {
        return -1;
    }
}

int UnixSocket::receive(char* buffer, int length) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(socket, &readfds);

    timeval timeout{};
    timeout.tv_sec = 0;
    timeout.tv_usec = SOCKET_SELECT_TIMEOUT * 1000;

    int result = select(socket + 1, &readfds, nullptr, nullptr, &timeout);

    if (result > 0 && FD_ISSET(socket, &readfds)) {
        return ::recv(socket, buffer, length, 0);
    } else if (result == 0) {
        return 0;
    } else {
        return -1;
    }
}

void UnixSocket::close() {
    if (socket >= 0) {
        ::close(socket);
        socket = -1;
    }
}
