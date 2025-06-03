#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <unordered_map>

using MessageMap = std::unordered_map<std::string, std::string>;

class Message {
    public:
        explicit Message(const MessageMap& m);

        bool isType(const std::string& type) const;
        std::string get(const std::string& key) const;

        const MessageMap& data() const { return message; };

        static std::string serialize(const Message& message);
        static Message deserialize(const char* data, int length);

    private:
        MessageMap message;
};

#endif
