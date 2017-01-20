#pragma once
#include "Board.hpp"
#include "Tools.hpp"
#include "Exceptions.hpp"

class Game {
private:
	const char* const file_name = "puz2-d.txt"; // "puz2-d.txt" "sudo-test1.txt"
public:
	Game();
	void run(Board &board);
	char menu_c(const char* title, int n, const char* menu[], 
		const string valid);
};