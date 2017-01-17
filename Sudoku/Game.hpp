#pragma once
#include "Board.hpp"
#include "Tools.hpp"
#include "Exceptions.hpp"

class Game {
private:
	const char* const file_name = "sudo-test1.txt";
	const char* const diag_name = "puz2-d.txt";
public:
	Game();
	void run(Board &board);
	char menu_c(const char* title, int n, const char* menu[], 
		const string valid);
};