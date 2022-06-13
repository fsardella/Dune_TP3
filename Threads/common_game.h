#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <list>
#include <iostream>
#include <string>

class Game {
	int house;
	int required;
	std::string game_name;
	int participants;
	public:
	Game(int ID_house, int num_required, std::string& name);
	void add_participant();
	std::string get_name();
	int get_num_bytes();
	int get_participants();
	int get_requiered();
	bool game_complete();
	~Game();
};

#endif /*__GAME_H__*/
