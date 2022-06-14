#include "server_gamedata.h"

GameData::GameData(const Game& game) : players(game.get_participants()),
                                       required(game.get_required()),
                                       game_name(game.get_name()) {}

std::string GameData::get_name() {
    return this->game_name;
}

int GameData::get_num_bytes() {
    return this->game_name.length();
}

int GameData::get_participants() {
    return this->players;
}

int GameData::get_required() {
    return this->required;
}


GameData::~GameData() {}
