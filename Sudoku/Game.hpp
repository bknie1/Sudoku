#pragma once
#include "Board.hpp"
#include "Tools.hpp"

#define INPUT_FILE "sudo-test1.txt"

class Game {
private:
public:
	Game();
	~Game();
	void run(Board &board);
	char menu_c(const char* title, int n, const char* menu[], 
		const string valid);
};