#ifndef SOCKET_WINDOWS_H
#define SOCKET_WINDOWS_H

#include "socket.h"

#include <winsock2.h>

class WindowsSocket : public Socket {
    public:
        WindowsSocket(SOCKET socket);
        ~WindowsSocket();

        bool connect(const char* host, int port) override;
        int send(const char* data, int length) override;
        int receive(char* buffer, int length) override;
        void close() override;

    private:
        SOCKET socket;
};

#endif
