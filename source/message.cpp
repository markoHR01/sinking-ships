#include "message.h"

Message::Message(const MessageMap& m) : message(m) {}

bool Message::isType(const std::string& type) const {
    auto it = message.find("type");
    return it != message.end() && it->second == type;
}

std::string Message::get(const std::string& key) const {
    auto it = message.find(key);
    if (it != message.end()) {
        return it->second;
    }
    return "";
}
