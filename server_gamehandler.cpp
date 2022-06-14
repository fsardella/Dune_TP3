#include "server_gamehandler.h"

GameHandler::GameHandler(Game newGame, talkerMap_t& talkerThreads):
                                        game(ActiveGame(std::move(newGame))),
                                        talkerThreads(talkerThreads) {}


void GameHandler::run() {
    Command comm;
    Broadcaster broad;
    broad.start();
    comm = commandQueue.pop();
    
}
    
GameHandler::~GameHandler() {
    this->join();
}
