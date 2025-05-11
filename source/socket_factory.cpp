#include "socket_factory.h"

#ifdef _WIN32
#include "socket_windows.h"
#include <winsock2.h>

Socket* createSocket() {
    SOCKET socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFD == INVALID_SOCKET) {
        return nullptr;
    }

    return new WindowsSocket(socketFD);
}

#else
#include "socket_unix.h"
#include <sys/socket.h>

Socket* createSocket() {
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        return nullptr;
    }

    return new UnixSocket(socketFD);
}

#endif
