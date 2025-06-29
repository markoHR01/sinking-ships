#include "network_thread.h"

#include <chrono>
#include <cstring>

NetworkThread::NetworkThread(Socket* s)
               : hasOutgoing(false),
                 hasIncoming(false),
                 socket(s),
                 running(false) {}

NetworkThread::~NetworkThread() {
    stop();
}

void NetworkThread::start() {
    if (!running) {
        running = true;
        thread = std::thread(&NetworkThread::run, this);
    }
}

void NetworkThread::stop() {
    if (running) {
        running = false;
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void NetworkThread::sendMessage(const Message& message) {
    std::lock_guard<std::mutex> lock(outMutex);
    out.push(message);
    hasOutgoing = true;
}

Message NetworkThread::readMessage() {
    if (!hasIncoming) return Message({});

    std::lock_guard<std::mutex> lock(inMutex);
    Message message = in.front();
    in.pop();

    if (in.empty()) hasIncoming = false;
    return message;
}

void NetworkThread::run() {
    char buffer[1024];

    while (running) {
        int received = socket->receive(buffer, sizeof(buffer));
        if (received > 0) {
            Message message = Message::deserialize(buffer, received);
            {
                std::lock_guard<std::mutex> lock(inMutex);
                in.push(message);
                hasIncoming = true;
            }
        }

        if (hasOutgoing) {
            std::lock_guard<std::mutex> lock(outMutex);
            Message message = out.front();

            std::string data = Message::serialize(message);
            int sent = socket->send(data.c_str(), static_cast<int>(data.size()));
            if (sent > 0) out.pop();

            if (out.empty()) hasOutgoing = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
