#pragma once
#include "Board.hpp"
#include "Tools.hpp"
#include "Exceptions.hpp"
#include "Viewer.hpp"
#include "BoardState.hpp"

class Game {
private:
	Board* board;
	// "puz2-d.txt" "sudo-test1.txt"
	const char* const file_name = "sudo-test1.txt"; 
	BoardState* create_board_state(Board* board);
	Stack undo, redo; // Derived from vector<BoardState*>
	void move();
public:
	Game();
	void run();
	char menu_c(const char* title, int n, const char* menu[], 
		const string valid);
};
