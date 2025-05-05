#include "socket_factory.h"

#ifdef _WIN32
#include "socket_windows.h"
Socket* createSocket() {
    return new WindowsSocket();
}
#else
#include "socket_unix.h"
Socket* createSocket() {
    return new UnixSocket();
}
#endif
