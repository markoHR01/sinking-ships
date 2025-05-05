#ifndef SOCKET_UNIX_H
#define SOCKET_UNIX_H

#include "socket.h"

class UnixSocket : public Socket {
    public:
        UnixSocket();
        ~UnixSocket();

        bool connect(const char* host, int port) override;
        bool send(const char* data, int length) override;
        int receive(char* buffer, int length) override;
        void close() override;
};

#endif
