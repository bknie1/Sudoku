#include "Board.hpp"

Board::Board() {
	fatal("Error: Missing input file in constructor.");
}
//-------------------------------------------------------------------------
Board::Board(const char* filename) {
	char ch;
	short row = 1;
	short col = 1;

	fIn.open(filename);
	if (!fIn.is_open() ) { fatal("Error: Input file missing."); }
	say("Input file found.");
	// Read and construct a board based on a max board size.
	for (short k = 0; k < MAX_SIZE; ++k) {
		ch = fIn.get();
		if (fIn.eof() ) { break; }
		bd[k] = Square(ch, row, col);
		if (col == MAX_COL) { ++row; col = 1; } else { ++col; }
	}
}
//-------------------------------------------------------------------------
Board::~Board() {

}
//-------------------------------------------------------------------------
//Square & Board::sub(int row, int col) {
//	Square s = (row - 1) * 9 + (col - 1);
//}
//-------------------------------------------------------------------------
ostream & Board::print(ostream& out) {
	for (short k = 0; k < MAX_SIZE; ++k) {
		bd[k].print(out);
	}
	return out;
}