/*	Program: Sudoku
	Description: A simple, console-based C++ implementation of a
	9x9 Sudoku board game.
	Header/Source Files: Sudoku.cpp, Tools.hpp/cpp, Square.hpp/cpp,
	Board.hpp/cpp, Cluster.hpp/cpp
*/
#include "Tools.hpp"
#include "Square.hpp"

#define INPUT_FILE "sudo-test1.txt"

/* Unit Test Prototypes */
void UT_State();

int main() {
	cout << "\t    ----SUDOKU----\n" << endl;
	UT_State();
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