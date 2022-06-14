#ifndef __SERVER_COMMAND_H__
#define __SERVER_COMMAND_H__

#include <string>

typedef struct command {
 public:
    std::string playerName;
    int x;
    int y;
} Command;

#endif
