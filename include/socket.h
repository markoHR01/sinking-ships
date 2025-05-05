#ifndef SOCKET_H
#define SOCKET_H

class Socket {
    public:
        virtual ~Socket() = default;

        virtual bool connect(const char* host, int port) = 0;
        virtual bool send(const char* data, int length) = 0;
        virtual int receive(char* buffer, int length) = 0;
        virtual void close() = 0;
};

#endif
