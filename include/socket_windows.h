#ifndef SOCKET_WINDOWS_H
#define SOCKET_WINDOWS_H

#include "socket.h"

class WindowsSocket : public Socket {
    public:
        WindowsSocket();
        ~WindowsSocket();

        bool connect(const char* host, int port) override;
        bool send(const char* data, int length) override;
        int receive(char* buffer, int length) override;
        void close() override;
};

#endif
