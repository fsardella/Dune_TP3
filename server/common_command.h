#ifndef __SERVER_COMMAND_H__
#define __SERVER_COMMAND_H__

#include <string>

#include <vector>
#include <stdint.h>

class Command {
    std::vector<uint8_t> command;
    size_t actTop;
    std::string sender;
    uint8_t type;

 public:
    Command();
    void changeSender(const std::string newName);
    void setType(const uint8_t newType);
    size_t size();
    bool isEmpty();
    uint8_t* getPointer();
    uint8_t getType();
    void reserve(const size_t newSize);
    std::string getSender();
    void add8BytesMessage(const uint8_t message);
    void add16BytesMessage(const uint16_t message);
    void add32BytesMessage(const uint32_t message);
    void addString(const std::string& sent);
    uint8_t pop8BytesMessage();
    uint16_t pop16BytesMessage();
    uint32_t pop32BytesMessage();
    std::string popString(const size_t length);
    ~Command();
};


#endif