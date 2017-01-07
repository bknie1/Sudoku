#include "Board.hpp"



Board::Board() {
	fatal("Error: Missing input file in constructor.");
}
//-------------------------------------------------------------------------
Board::Board(const char* filename) {
	const char* printT[] = { "Row", "Column", "Block" };
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
		board[k] = Square(ch, row, col);
		if (col == MAX_COL) { ++row; col = 1; } else { ++col; }
	}
	create_clusters();
}
//-------------------------------------------------------------------------
Board::~Board() {

}
//-------------------------------------------------------------------------
void Board::create_clusters() {
	// clusters[27] - To store created clusters.
	// board[81]. Use these to create clusters.

	cerr << "\n\t\tCLUSTER TEST: CREATE" << endl;
	build_cl_row(); // Build Row Clusters: 0 - 8
	build_cl_col();	// Build Column Clusters: 9 - 17
	build_cl_blk();	// Build Block Clusters: 18 - 27

	//for (int k = 1; k < MAX_SIZE + 1; k++)

		//if (k % 9 == 0 && k < 27) {
		//	cluster[1] += board[k - 7];
		//	cluster[1] += board[k - 8];
		//	cluster[1] += board[k - 9];
		//}
		//if (!(k % 9) && k < 27) {
		//	cluster[2] += board[k - 5];
		//	cluster[2] += board[k - 6];
		//	cluster[2] += board[k - 7];
		//}
		//
		//if (!(k % 9) && k < 27) {
		//	cluster[3] += board[k - 3];
		//	cluster[3] += board[k - 2];
		//	cluster[3] += board[k - 1];
		//}
}
//-------------------------------------------------------------------------
void Board::build_cl_row() {
	// Outer iterates through to create n Clusters based on col size.
	// Inner gets the 9 relevant squares related to a persistent index (s).
	
	Square* cl_squares[MAX_COL]; // Squares to be assigned to cluster.
	int board_i = 0;

	for (int ci = 0; ci < MAX_COL; ++ci) { // Creates Clusters
		for (int k = 0 ; k < MAX_COL; ++board_i, ++k) { // Gathers Squares
			cl_squares[k] = &board[board_i];
		}
		clusters[ci] = Cluster(ROW, cl_squares);
		clusters[ci].print(); // DEBUG
	}
}
//-------------------------------------------------------------------------
void Board::build_cl_col() {
	// See build_cl_row() for general description.
	// col_start persists to iterate through columns.
	// board_i will be init'd by col_start and change during the op.
	
	Square* cl_squares[MAX_COL]; // Squares to be assigned to cluster.
	int col_start = 0, board_i;
	for (int ci = 0; ci < MAX_COL; ++ci) { // Creates Clusters
		board_i = col_start;
		for (int k = 0; k < MAX_COL; ++k, board_i += MAX_COL) {
			cl_squares[k] = &board[board_i];
		}
		++col_start; // 1,1 -> 1,2 -> 1,3 etc. Change columns/starting point.
		clusters[ci] = Cluster(COL, cl_squares);
		clusters[ci].print(); // DEBUG
	}
}
//-------------------------------------------------------------------------
void Board::build_cl_blk() {

}
//-------------------------------------------------------------------------
Square & Board::sub(int row, int col) {
	Square s; // Placeholder.
	return s; // Placeholder.
}
//-------------------------------------------------------------------------
ostream & Board::print(ostream& out) {
	for (short k = 0; k < MAX_SIZE; ++k) {
		board[k].print(out);
	}
	return out;
}