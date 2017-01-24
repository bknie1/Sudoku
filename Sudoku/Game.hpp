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
	Stack undo, redo; // Derived from vector<BoardState*>
	void move();
	void undo_move();
	void redo_move();
	void save_game();
	void load_game();
public:
	Game();
	void run();
	char menu_c(const char* title, int n, const char* menu[], 
		const string valid);
};
