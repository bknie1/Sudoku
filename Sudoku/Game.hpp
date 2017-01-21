#pragma once
#include "Board.hpp"
#include "Tools.hpp"
#include "Exceptions.hpp"
#include "Viewer.hpp"

class Game {
private:
	Board* board;
	Viewer fancyView;
	const char* const file_name = "sudo-test1.txt"; // "puz2-d.txt" "sudo-test1.txt"
public:
	Game();
	void run();
	char menu_c(const char* title, int n, const char* menu[], 
		const string valid);
};