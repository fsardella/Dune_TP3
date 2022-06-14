#ifndef __CLIENT_INPUT_H__
#define __CLIENT_INPUT_H__

#include <utility>

class ClientInput {
	int posX;
	int posY;
public:
	ClientInput(int x, int y);
	~ClientInput();
	int getPosX();
	int getPosY();

    ClientInput(const ClientInput&) = delete;
    ClientInput& operator=(const ClientInput&) = delete;

    ClientInput(ClientInput&&);
    ClientInput& operator=(ClientInput&&);

};

#endif /*__CLIENT_INPUT_H__*/