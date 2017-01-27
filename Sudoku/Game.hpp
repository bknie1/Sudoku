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
	Stack undo, redo; // Derived from vector<BoardState*>
	void move();
	void undo_move();
	void redo_move();
	void save_game(const char* output_file);
	void load_game(const char* input_file);
	void load_new_game();
public:
	Game();
	~Game();
	void run();
	void load_menu();
	char menu_c(const char* title, int n, const char* menu[], 
		const string valid);
};