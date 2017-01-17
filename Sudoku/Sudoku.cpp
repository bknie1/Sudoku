/*	Program: Sudoku
	Description: A simple, console-based C++ implementation of a
	9x9 Sudoku board game.
	Header/Source Files: Sudoku.cpp, Tools.hpp/cpp, Square.hpp/cpp,
	Board.hpp/cpp, Cluster.hpp/cpp
*/
#include <windows.h>
#include "Game.hpp"
#include "Board.hpp"
#include "Cluster.hpp"
#include "Square.hpp"
#include "Tools.hpp"

// #define INPUT_FILE "sudo-test1.txt" // Game owns this now.

/* Unit Test Prototypes */
void music_for_fun();
void ut_state();
void ut_square();
void ut_board_and_cluster();

int main() {
	cout << "\t    SUDOKU\n" << endl;
	Game g;
	//ut_board_and_cluster();
}

void ut_state() {
	cerr << "\n\tSTATE TEST: MOVE" << endl;

	State st1 = State();
	st1.move('1'); // Valid.
	st1.print(cout);
	cerr << endl;

	State st2 = State();
	st2.move('2'); // Valid.
	st2.print(cout);
	cerr << endl;

	State st3 = State();
	st3.move('a'); // Invalid. Replace w/ dash.
	st3.print(cout);
	cerr << endl;

	State st4 = State();
	st4.move('0'); // Invalid. Replace w/ dash.
	st4.print(cout);
	cerr << endl;
}

void ut_square() {
	cerr << "\n\t\tSQUARE TEST: COORDINATED PLACEMENT" << endl;

	Square sq1 = Square('1', 1, 1);
	sq1.print(cout);
	cerr << endl;

	Square sq2 = Square('2', 2, 2);
	sq2.print(cout);
	cerr << endl;
}

void ut_board_and_cluster() {
	cerr << "========================================================" << endl;
	cerr << "\n\t\tBOARD TEST: INPUT FILE" << endl;
	//Board &board = Board(INPUT_FILE);
	cerr << "\n\t\tBOARD TEST: AFTER SHOOP\n" << endl;
	//&board.print(cout);
	//board.draw_board();
}

void music_for_fun() {
	//ascending pitch beep
	for (int i = 100; i < 1000; i += 200) {
		Beep(i, 100);
	}
}