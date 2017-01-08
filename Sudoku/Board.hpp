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
#define MAX_COL 9	// Max column/row size. Used to adjust coords.
#define BLK_WID MAX_COL/3	// MAX_COL / 3
#define BOARD_SIZE MAX_COL * MAX_COL // MAX_COL * MAX_COL

enum clusterT { ROW, COL, BLK };
static const char* printT[3];

class Board {
private:
	ifstream fIn;
	Square board[BOARD_SIZE];
	Cluster clusters[27];
	void create_clusters();
	void build_cl_row();
	void build_cl_col();
	void build_cl_blk();
	Square& sub(int row, int col);
public:
	Board();
	Board(const char* filename);
	~Board();

	ostream& print(ostream&);
};
inline ostream& operator<< (ostream& out, Board& b) { return out; }
