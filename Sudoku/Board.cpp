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
	for (short k = 0; k < BOARD_SIZE; ++k) {
		ch = fIn.get();
		if (fIn.eof() ) { break; }
		board[k] = Square(ch, row, col);
		if (col == MAX_COL) { ++row; col = 1; } else { ++col; }
	}
	create_clusters();
}
//-------------------------------------------------------------------------
Board::~Board() {
	// cerr << "Board destroyed. << endl;
}
//-------------------------------------------------------------------------
void Board::create_clusters() {
	// clusters[27] - To store created clusters.
	// board[81]. Use these to create clusters.

	cerr << "\n\t\tCLUSTER TEST: CREATE" << endl;
	build_cl_row(); // Build Row Clusters: 0 - 8
	cout << "\t=========================================\n" << endl;
	build_cl_col();	// Build Column Clusters: 9 - 17
	cout << "\t=========================================\n" << endl;
	build_cl_blk();	// Build Block Clusters: 18 - 27
	cout << "\t=========================================\n" << endl;
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
		
		clusters[ci].print(cout); // DEBUG

		say("Adding ROW cluster to Square's cluster array.");
		for (int k = 0; k < MAX_COL; ++k) {
			cl_squares[k]->addCluster(&clusters[ci]);
		}
	}
}
//-------------------------------------------------------------------------
void Board::build_cl_col() {
	// See build_cl_row() for general description.
	// col_start persists to help iterate through columns.
	// board_i will pick up where the previous inner op ended.
	
	Square* cl_squares[MAX_COL]; // Squares to be assigned to cluster.
	int col_start = 0, board_i;

	for (int ci = 0; ci < MAX_COL; ++ci) { // Creates Clusters
		board_i = col_start;
		for (int k = 0; k < MAX_COL; ++k, board_i += MAX_COL) {
			cl_squares[k] = &board[board_i];
		}
		++col_start; // 1,1 -> 1,2 -> 1,3 etc. Change columns/starting point.
		clusters[ci] = Cluster(COL, cl_squares);

		clusters[ci].print(cout); // DEBUG

		say("Adding COL cluster to Square's cluster array.");
		for (int k = 0; k < MAX_COL; ++k) {
			cl_squares[k]->addCluster(&clusters[ci]);
		}
	}
}
//-------------------------------------------------------------------------
void Board::build_cl_blk() {
	// See build_cl_row() for general description.
	// Creates 3x3 block clusters starting with 1,1.
	// Once it hits the last block in a row (ex. 3 out of 3 on size 9.
	// It recognizes and increments the board index to skip the next two rows.
	// Otherwise, there would be overlapping blocks.
	Square* cl_squares[MAX_COL]; // To be assigned to cluster.
	int blk_start = 0, board_i;

	for (int ci = 0; ci < MAX_COL; ++ci) { // Creates Clusters.
		board_i = blk_start;
		for (int k = 0; k < MAX_COL; ++k) {
			cl_squares[k] = &board[board_i];
			if (!((board_i + 1) % BLK_WID)) { 
				board_i += (MAX_COL + 1) - BLK_WID; } 
			else { ++board_i; }
		}
		if (!((1 + ci) % BLK_WID)) { blk_start += BLK_WID * (BLK_WID * 2 + 1); }
		else { blk_start += BLK_WID; }
		clusters[ci] = Cluster(BLK, cl_squares);

		clusters[ci].print(cout); // DEBUG
		
		say("Adding BLK cluster to Square's cluster array.\n");
		for (int k = 0; k < MAX_COL; ++k) {
			cl_squares[k]->addCluster(&clusters[ci]);
		}
	}
}
//-------------------------------------------------------------------------
Square & Board::sub(int row, int col) {
	Square s; // Placeholder.
	return s; // Placeholder.
}
//-------------------------------------------------------------------------
ostream & Board::print(ostream& out) {
	for (short k = 0; k < BOARD_SIZE; ++k) {
		board[k].print(out);
	}
	return out;
}