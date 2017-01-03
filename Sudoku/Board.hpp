/*	Program: Sudoku
Description: A simple, console-based C++ implementation of a
9x9 Sudoku board game. See Sudoku.cpp or the Readme for more.
*/

/*	Class Description: Board is responsible for creating the 9x9 grid
	on which each Square sits.
*/

#pragma once
#include "tools.hpp"
#include "Square.hpp"
#define MAX_SIZE 81 // 9 x 9 board size limit.
#define MAX_COL 9	// Max column/width. Used to adjust coords.

enum clusterT { Type1, Type2, Type3 };
const char* printT[];

class Board {
private:
	ifstream fIn;
	Square bd[MAX_SIZE];
public:
	Board();
	Board(const char* filename);
	~Board();
	Square& sub(int j, int k);
	ostream& print(ostream&);
};
inline ostream& operator<< (ostream& out, Board& b) { return out; }