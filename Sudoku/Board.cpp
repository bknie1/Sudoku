#include "Board.hpp"

Board::Board() {
	fatal("Error: Missing input file in constructor.");
}
//-------------------------------------------------------------------------
Board::Board(const char* filename) {
	const char* printT[] = { "Row", "Column", "Block" };
	string new_value;
	char value;
	short row = 1;
	short col = 1;
	dash_count = 0;

	fIn.open(filename);
	if (!fIn.is_open()) { fatal("Error: Input file missing."); }
	else { say("Input file found."); } // Else unecessary, but due diligence.

	// Read and construct a board using the passed file. Ex. 9x9 = 81 Sq's
	for (short k = 0; k < BOARD_SIZE; ++k) {
		fIn >> ws;
		value = fIn.get();
		if (fIn.eof()) { break; }
		board[k] = Square(value, row, col);
		if (value == '-') { ++dash_count; }
		if (col == MAX_COL) { ++row; col = 1; }
		else { ++col; }
	}
	cerr << "\n\t\tBOARD TEST: BEFORE SHOOP" << endl;
	//print(cout);
	create_clusters();
	//draw_board();
	initial_shoop();
	fIn.close();
	
	//cout << "Dash Count: " << dash_count << endl; // DEBUG
}
//-------------------------------------------------------------------------
Board::~Board() {
	// cerr << "Board destroyed. << endl;
}
//-------------------------------------------------------------------------
void Board::draw_board() {
	char value;
	cout << "\n|======================================|\n|";
	for (int k = 0; k < BOARD_SIZE; ++k) {
		value = board[k].getValue();
		cout << " " << value << " |";
		if (((k + 1) % 3) == 0) { cout << "|"; }
		if (k + 1 != BOARD_SIZE) {
			if (((k + 1) % 9) == 0) {
				cout << "\n|";
				cout << "--------------------------------------|\n|";
			}
			if (((k + 1) % 27) == 0) {
				//cout << "--------------------------------------|\n|"
				cout << "======================================|\n|";;
			}
		}
		else { cout << "\n|"; }
	}
	cout << "======================================|\n" << endl;
}
//-------------------------------------------------------------------------
bool Board::is_done() {
	// Returns true when all squares are filled.
	// Check after each move?
	//Based on Board's dash count.
	if (!dash_count) { return true; }
	else { cout << dash_count << " dashes left." << endl; return false; }
}
//-------------------------------------------------------------------------
void Board::create_clusters() {
	// clusters[27] - To store created clusters.
	// board[81]. Use these to create clusters.
	cerr << "\n\t\tCLUSTER TEST: CREATE\n" << endl;
	build_cl_row(); // Build Row Clusters: 0 - 8
	build_cl_col();	// Build Column Clusters: 9 - 17
	build_cl_blk();	// Build Block Clusters: 18 - 27
}
//-------------------------------------------------------------------------
void Board::build_cl_row() {
	// Outer iterates through to create n Clusters based on col size.
	// Inner gets the 9 relevant squares related to a persistent index (s).

	Square* cl_squares[MAX_COL]; // Squares to be assigned to cluster.
	int board_i = 0;

	for (int ci = 0; ci < MAX_COL; ++ci) { // Creates Clusters
		for (int k = 0; k < MAX_COL; ++board_i, ++k) { // Gathers Squares
			cl_squares[k] = &board[board_i];
		}
		clusters[ci] = Cluster(ROW, cl_squares);
		//clusters[ci].print(cout); // DEBUG
		// Each Square should get a ROW cluster added to clues[].
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

	for (int ci = MAX_COL; ci < MAX_COL * 2; ++ci) { // Creates Clusters
		board_i = col_start;
		for (int k = 0; k < MAX_COL; ++k, board_i += MAX_COL) {
			cl_squares[k] = &board[board_i];
		}
		++col_start; // 1,1 -> 1,2 -> 1,3 etc. Change columns/starting point.
		clusters[ci] = Cluster(COL, cl_squares);
		//clusters[ci].print(cout); // DEBUG
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

	for (int ci = MAX_COL * 2; ci < MAX_COL * 3; ++ci) { // Creates Clusters.
		board_i = blk_start;
		for (int k = 0; k < MAX_COL; ++k) {
			cl_squares[k] = &board[board_i];
			if (!((board_i + 1) % 3) ) {
				board_i += (MAX_COL + 1) - BLK_WID;
			}
			else { ++board_i; }
		}
		if (!((1 + ci) % 3)) { blk_start += BLK_WID * 7; }
		else { blk_start += BLK_WID; }
		clusters[ci] = Cluster(BLK, cl_squares);
		//clusters[ci].print(cout); // DEBUG
		for (int k = 0; k < MAX_COL; ++k) {
			cl_squares[k]->addCluster(&clusters[ci]);
		}
		// Debugging Create Print
		//for (int k = 0; k < MAX_COL; ++k) {
		//	cout << "Clue Clusters so far:\n" << endl;
		//	cl_squares[k]->print_clues(cout);
		//}
	}
}
//-------------------------------------------------------------------------
void Board::initial_shoop() {
	// Once the board has been constructed, use this to 'initialize'
	// All of the possibilities lists in each Square by Cluster.
	cerr << "\t\tCLUSTER TEST: INITIAL SHOOP" << endl; // DEBUG
	char value;
	for (int k = 0; k < BOARD_SIZE; ++k) {
		value = board[k].getValue();
		if (isdigit(value) ) { board[k].move(value); }
	}
}
//-------------------------------------------------------------------------
int Board::sub(int row, int col) {
	// Algorithm that determines loc in array based on coordinates.
	int loc = (row - 1) * 9 + (col - 1);
	return loc;
}
//-------------------------------------------------------------------------
void Board::move(int row, int col, char value) {
	int loc = sub(row, col);
	// If coordinates exceed the board:
	if (row < MAX_COL || col < MAX_COL) { 
		if (!board[loc].isFixed()) { // Is it a fixed Square?
			if (isdigit(value)) {
				board[loc].move(value);
				--dash_count;
			}
			else if (value == '-') { // A dash entry?
				board[loc].move('-'); // Hard pass. We know it's a dash.
				++dash_count;
			}
			else { say("Error: Value must be a number or dash."); }
		}
		else { say("Error: Square is fixed. Cannot change values."); }
	}
	else { say("Error: Coordinates exceed board size."); }
}
//-------------------------------------------------------------------------
ostream & Board::print(ostream& out) {
	for (short k = 0; k < BOARD_SIZE; ++k) {
		board[k].print(out);
	}
	return out;
}