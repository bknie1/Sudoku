/*	Program: Sudoku
Description: A simple, console-based C++ implementation of a
9x9 Sudoku board game. See Sudoku.cpp or the Readme for more.
*/

/*	Class Description: Board is responsible for creating the 9x9 grid
	on which each Square sits.
*/

#pragma once
#include "Tools.hpp"
#include "Square.hpp"
#include "Cluster.hpp"
#define MAX_SIZE 81 // 9 x 9 board size limit.
#define MAX_COL 9	// Max column/width. Used to adjust coords.

enum clusterT { row, col, blk };
const char* printT[];

class Board {
private:
	ifstream fIn;
	Square bd[MAX_SIZE];
	Square& sub(int row, int col);
public:
	Board();
	Board(const char* filename);
	~Board();
	ostream& print(ostream&);
};
inline ostream& operator<< (ostream& out, Board& b) { return out; }
