#include "Board.hpp"

Board::Board() {
	fatal("Error: Missing input file in constructor.");
}
//-------------------------------------------------------------------------
Board::Board(const char* filename) {
	char next;
	short row = 1;
	short col = 1;

	fIn.open(filename);
	if (!fIn.is_open() ) { fatal("Error: Input file missing."); }
	say("Input file found.");
	for (short k = 0; k < MAX_SIZE; ++k) {
		next = fIn.get();
		if (fIn.eof() ) { break; }
		bd[k] = Square(next, row, col);
		if (col == MAX_COL) { ++row; col = 1; } else { ++col; }
	}
}
//-------------------------------------------------------------------------
Square& Board::sub(int j, int k) {
	short row; short col;
	// (j - 1)  9 + (k - 1) ???
	for (short k = 0; k < MAX_SIZE; ++k) {
		row = bd[k].getRow(); col = bd[k].getCol();
		if (j == row && k == col) { return bd[k]; }
	}
}
//-------------------------------------------------------------------------
ostream & Board::print(ostream& out) {
	for (short k = 0; k < MAX_SIZE; ++k) {
		bd[k].print(out);
	}
	return out;
}
//-------------------------------------------------------------------------
Board::~Board() {

}