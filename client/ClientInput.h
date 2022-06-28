#ifndef __CLIENT_INPUT_H__
#define __CLIENT_INPUT_H__

#include <utility>

class ClientInput {
	int operation;
	int type;
	int param1 = -1;
	int param2 = -1;

public:
	ClientInput(int operation, int type, int param1, int param2);
	ClientInput(int operation, int type);
	~ClientInput();

	int getOperation();
	int getType();
	int getParam1();
	int getParam2();

    ClientInput(const ClientInput&) = delete;
    ClientInput& operator=(const ClientInput&) = delete;

    ClientInput(ClientInput&&);
    ClientInput& operator=(ClientInput&&);
};

#endif /*__CLIENT_INPUT_H__*/