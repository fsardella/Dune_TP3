#include "ClientInput.h"
#include <utility>


ClientInput::ClientInput(int x, int y): posX(x), posY(y){

}

ClientInput::ClientInput(ClientInput &&other) {
	 this->posX = other.posX;
	 this->posY = other.posY;
}

ClientInput& ClientInput::operator=(ClientInput &&other) {
	if(this == &other) return *this;

	this->posX = other.posX;
	this->posY = other.posY;

	return *this;
}

int ClientInput::getPosX() {
	return posX;
}

int ClientInput::getPosY() {
	return posY;
}

ClientInput::~ClientInput() {
	
}
