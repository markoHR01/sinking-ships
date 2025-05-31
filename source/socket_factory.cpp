#include "socket_factory.h"

#ifdef _WIN32
#include "socket_windows.h"
#include <winsock2.h>

Socket* createSocket() {
    SOCKET socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFD == INVALID_SOCKET) {
        return nullptr;
    }

    u_long mode = 1;
    if (ioctlsocket(socketFD, FIONBIO, &mode) != 0) {
        closesocket(socketFD);
        return nullptr;
    }

    return new WindowsSocket(socketFD);
}

#else
#include "socket_unix.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

Socket* createSocket() {
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        return nullptr;
    }

    int flags = fcntl(socketFD, F_GETFL, 0);
    if (flags == -1 || fcntl(socketFD, F_SETFL, flags | O_NONBLOCK) == -1) {
        close(socketFD);
        return nullptr;
    }

    return new UnixSocket(socketFD);
}

#endif
