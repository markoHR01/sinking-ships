#ifndef SOCKET_UNIX_H
#define SOCKET_UNIX_H

#include "socket.h"

class UnixSocket : public Socket {
    public:
        explicit UnixSocket(int socket);
        ~UnixSocket();

        bool connect(const char* host, int port) override;
        int send(const char* data, int length) override;
        int receive(char* buffer, int length) override;
        void close() override;

    private:
        int socket;
};

#endif
