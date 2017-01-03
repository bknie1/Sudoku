/*	Program: Sudoku
	Description: A simple, console-based C++ implementation of a
	9x9 Sudoku board game.
	Header/Source Files: Sudoku.cpp, Tools.hpp/cpp, Square.hpp/cpp,
	Board.hpp/cpp, Cluster.hpp/cpp
*/
#include "Tools.hpp"
#include "Square.hpp"
#include "Board.hpp"

#define INPUT_FILE "sudo-test1.txt"

/* Unit Test Prototypes */
void UT_State();
void UT_Square();
void UT_Board();

int main() {
	cout << "\t    ----SUDOKU----\n" << endl;
	UT_State();
	UT_Square();
	UT_Board();
}

void UT_State() {
	cerr << "\n\t\UNIT TEST: STATE" << endl;

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

void UT_Square() {
	cerr << "\n\t\tSQUARE TEST: COORDINATED PLACEMENT" << endl;

	Square sq1 = Square('1', 1, 1);
	sq1.print(cout);
	cerr << endl;

	Square sq2 = Square('2', 2, 2);
	sq2.print(cout);
	cerr << endl;
}

void UT_Board() {
	cerr << "\n\t\tBOARD TEST: INPUT FILE" << endl;
	Board &board = Board(INPUT_FILE);
	cerr << "\n\t\tBOARD TEST: PRINT" << endl;
	&board.print(cout);
}