#include "server_inputguy.h"

InputGuy::InputGuy(Listener& listeningThread, BlockingQueue<Game>& readyGames,
                   talkerMap_t& userThreads):
                                              listeningThread(listeningThread),
                                              readyGames(readyGames),
                                              userThreads(userThreads) {}

void InputGuy::run() {    
    std::string input;
	while (input != "q") {
		std::cin >> input;
	}
    this->listeningThread.stopListening();
    this->readyGames.close();
    for (auto& t : this->userThreads) {
        t.second->close();
    }
}

InputGuy::~InputGuy() {
    this->join();    
}
