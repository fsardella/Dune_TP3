#include "ClientInput.h"
#include <utility>


ClientInput::ClientInput(int operation, int param1): operation(operation), param1(param1)
{}

ClientInput::ClientInput(int operation, int param1, int param2, int param3)
: operation(operation), param1(param1), param2(param2), param3(param3)
{}

ClientInput::ClientInput(int operation, int param1, int param2)
: operation(operation), param1(param1), param2(param2)
{}

ClientInput::ClientInput(ClientInput &&other) {
	this->operation = other.operation;
	this->param1 = other.param1;
	this->param2 = other.param2;
	this->param3 = other.param3;
}

ClientInput& ClientInput::operator=(ClientInput &&other) {
	if(this == &other) return *this;

	this->operation = other.operation;
	this->param1 = other.param1;
	this->param2 = other.param2;
	this->param3 = other.param3;

	return *this;
}

int ClientInput::getOperation() {
	return operation;
}

int ClientInput::getParam1() {
	return param1;
}

int ClientInput::getParam2() {
	return param2;
}

int ClientInput::getParam3() {
	return param3;
}

ClientInput::~ClientInput() {
	
}
