#ifndef __CLIENT_INPUT_H__
#define __CLIENT_INPUT_H__

#include <utility>

class ClientInput {
    int operation;
    int param1 = -1;
    int param2 = -1;
    int param3 = -1;

 public:
    ClientInput(int operation, int param1);
    ClientInput(int operation, int param1, int param2);
    ClientInput(int operation, int param1, int param2, int param3);
    ~ClientInput();

    int getOperation();
    int getParam1();
    int getParam2();
    int getParam3();

    ClientInput(const ClientInput&) = delete;
    ClientInput& operator=(const ClientInput&) = delete;

    ClientInput(ClientInput&&);
    ClientInput& operator=(ClientInput&&);
};

#endif /*__CLIENT_INPUT_H__*/
