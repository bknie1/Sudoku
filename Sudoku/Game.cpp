#include "Game.hpp"

Game::Game() {
	// Creates a Board consisting of 'n' Squares.
	// n = BOARD_SIZE / (BOARD_SIZE / 3), probably.
	Board &board = Board(INPUT_FILE);
	//&board.print(cout); // DEBUG
	//board.draw_board(); // DEBUG
	run(board);
}
//-------------------------------------------------------------------------
Game::~Game() {

}
//-------------------------------------------------------------------------
void Game::run(Board &board) {
	// Print the Board, Menu, and an actions menu.
	short sel;
	short row;
	short column;
	char value;
	for (;;) {
		// Returns true? There are no more dashes/all spots filled.
		if (board.is_done() ) { break; }
		&board.print(cout);
		board.draw_board();
		cout << "1.\tMove" << endl;
		cout << "2.\tUndo" << endl;
		cout << "3.\tRedo" << endl;
		cout << "4.\tSave Game" << endl;
		cout << "5.\tRestore Game" << endl;
		cout << "6.\tQuit and Discard Game" << endl;

		cout << "Selection: ";
		cin >> sel;

		switch (sel) {
		case 1: // Move
			cout << "Input Row: ";
			cin >> row;
			cout << "Input Column: ";
			cin >> column;
			cout << "Input Value: ";
			cin >> value;
			board.move(row, column, value);
			break;
		case 2: // Undo

			break;
		case 3: // Redo

			break;
		case 4: // Save Game

			break;
		case 5: // Restore Game

			break;
		case 6: // Quit and Discard Game

			return;
		default:
			say("Error: Invalid input.");
			break;
		}
	}
	say("Congratulations, you've won!");
}