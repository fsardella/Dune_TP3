#include "ClientInput.h"
#include <utility>


ClientInput::ClientInput(int operation, int type): operation(operation), type(type)
{}

ClientInput::ClientInput(int operation, int type, int param1, int param2)
: operation(operation), type(type), param1(param1), param2(param2)
{}

ClientInput::ClientInput(ClientInput &&other) {
	this->operation = other.operation;
	this->type = other.type;
	this->param1 = other.param1;
	this->param2 = other.param2;
}

ClientInput& ClientInput::operator=(ClientInput &&other) {
	if(this == &other) return *this;

	this->operation = other.operation;
	this->type = other.type;
	this->param1 = other.param1;
	this->param2 = other.param2;

	return *this;
}

int ClientInput::getOperation() {
	return operation;
}

int ClientInput::getType() {
	return type;
}

int ClientInput::getParam1() {
	return param1;
}

int ClientInput::getParam2() {
	return param2;
}

ClientInput::~ClientInput() {
	
}
