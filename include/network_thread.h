#ifndef NETWORK_THREAD_H
#define NETWORK_THREAD_H

#include <thread>
#include <atomic>
#include <queue>
#include <mutex>

#include "socket.h"
#include "message.h"

class NetworkThread {
    public:
        explicit NetworkThread(Socket* s);
        ~NetworkThread();

        void start();
        void stop();

        void sendMessage(const Message& message);
        Message readMessage();

        std::atomic<bool> hasOutgoing;
        std::atomic<bool> hasIncoming;

    private:
        void run();

        Socket* socket;

        std::thread thread;
        std::atomic<bool> running;

        std::queue<Message> out;
        std::queue<Message> in;

        std::mutex outMutex;
        std::mutex inMutex;
};

#endif
