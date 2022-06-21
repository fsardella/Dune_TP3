#include "server_inputguy.h"

InputGuy::InputGuy(Listener& listeningThread, BlockingQueue<Game>& readyGames):
                                              listeningThread(listeningThread),
                                              readyGames(readyGames) {}

void InputGuy::run() {    
    std::string input;
	while (input != "q") {
		std::cin >> input;
	}
    this->listeningThread.stopListening();
    this->readyGames.close();
}

InputGuy::~InputGuy() {
    this->join();    
}
