#ifndef __SERVER_COMMAND_H__
#define __SERVER_COMMAND_H__

#include <string>

#include <vector>
#include <stdint.h>
//typedef struct command {
 //public:
    //std::string playerName;
    //int x;
    //int y;
//} Command;

class Command {
    std::vector<uint8_t> command;
    size_t actTop;
    std::string sender;
    uint8_t type;

 public:
    Command();
    void changeSender(std::string newName);
    void setType(uint8_t newType);
    size_t size();
    bool isEmpty();
    uint8_t* getPointer();
    uint8_t getType();
    void reserve(size_t newSize);
    std::string getSender();
    void add8BytesMessage(uint8_t message);
    void add16BytesMessage(uint16_t message);
    uint8_t pop8BytesMessage();
    uint16_t pop16BytesMessage();
    ~Command();
};


#endif
