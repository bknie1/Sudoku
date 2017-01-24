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
#include "CanView.hpp" // GUI

class BoardState;

#define BOARD_SIZE 81 // MAX_COL * MAX_COL

enum clusterT { ROW, COL, BLK, DIA };
static const char* printT[4];

//-------------------------------------------------------------------------
// 't'
class Board : public CanView {
protected:
	ifstream fIn;
	Square board[BOARD_SIZE];
	Cluster clusters[27];
	void create_clusters(); // Helper
	void build_cl_row();	// Helper, called by create_clusters()
	void build_cl_col();	// Helper, called by create_clusters()
	void build_cl_blk();	// Helper, called by create_clusters()
	void initial_shoop();	// Board ready, so shoop all values.
	int sub(int row, int col) const;
	short dash_count;

public:
	Board() = default;
	Board(const char* filename);
	bool move(int row, int col, char val);
	State get_square(int square_loc) const;
	void draw_board(); // User friendly view.
	bool is_done();
	void restore_state(BoardState* bs);
	ostream& save_game(ofstream& fOut);

	char getMarkChar(int row, int col) const;
	string getPossibilityString(int row, int col) const;

	Square& operator[](int k) { return this->board[k]; }

	ostream& print(ostream&);
};
//-------------------------------------------------------------------------
// 'd'
class Diagonal_Board : public Board {
private:
	Cluster clusters[29]; // Overrides Board's '27'. Replace with Ctor prob.
	void create_clusters();
	void build_cl_diag1();
	void build_cl_diag2();
public:
	Diagonal_Board() = default;
	Diagonal_Board(const char* filename);
};

inline ostream& operator<< (ostream& out, Board& b) {
	// cout << b << endl;
	b.print(out);
	return out;
}