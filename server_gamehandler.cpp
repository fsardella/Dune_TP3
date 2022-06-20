#include "server_gamehandler.h"

#include <list>
#include <string>
#include <utility>

GameHandler::GameHandler(Game newGame, talkerMap_t& talkerThreads):
                                        game(ActiveGame(std::move(newGame))) {
    std::list<std::string> names = this->game.getPlayerNames();
    sketch_t gameMapSketch = this->game.getMapSketch();
    for (std::string name : names) {
        this->playersQueue[name] = std::move(BlockingQueue<Command>());
        talkerThreads[name].startPlaying(&this->commandQueue, gameMapSketch,
                                         this->playersQueue[name]);
    }
}



void GameHandler::run() {
    Command comm;
    Broadcaster broad(this->game, this->playersQueue, playersConnected);
    broad.start();
    // TimeMaster.start()
    while (this->game.isAlive()) {
        comm = commandQueue.pop();
        this->processCommand(comm);
    }
}
    
GameHandler::~GameHandler() {
    this->join();
}
