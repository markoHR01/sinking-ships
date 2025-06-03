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

std::string Message::serialize(const Message& message) {
    std::string serialized;

    const MessageMap& data = message.data();

    for (const auto& [key, value] : data) {
        serialized += key + "=" + value + "\n";
    }

    return serialized;
}

Message Message::deserialize(const char* data, int length) {
    MessageMap map;
    std::string input(data, length);
    size_t start = 0;

    while (start < input.size()) {
        size_t end = input.find('\n', start);
        if (end == std::string::npos) break;

        std::string line = input.substr(start, end - start);
        size_t separator = line.find('=');
        if (separator != std::string::npos) {
            std::string key = line.substr(0, separator);
            std::string value = line.substr(separator + 1);
            map[key] = value;
        }

        start = end + 1;
    }

    return Message(map);
}
