#include "Board.hpp"
#include "BoardState.hpp"

Board::Board() {
	short row = 1;
	short col = 1;
	dash_count = 0;

	for (short k = 0; k < BOARD_SIZE; ++k) {
		board[k] = Square('-', row, col);
		++dash_count;
		if (col == 9) { ++row; col = 1; }
		else { ++col; }
	}

	create_clusters();
	initial_shoop();
}

//-------------------------------------------------------------------------
Board::Board(const char* filename) {
	const char* printT[] = { "Row", "Column", "Block", "Diagonal" };
	string new_value;
	char value;
	short row = 1;
	short col = 1;
	dash_count = 0;
	string junk;

	say("Creating Traditional Board");

	fIn.open(filename);
	fIn >> junk; // get the t

	// Read and construct a board using the passed file. Ex. 9x9 = 81 Sq's
	// First line will feature the puzzle type. ( (t)raditional, (d)iagonal
	// The following 9 are the puzzle.
	for (short k = 0; k < BOARD_SIZE; ++k) {
		fIn >> ws;
		value = fIn.get();
		if (fIn.eof()) { break; }
		board[k] = Square(value, row, col);
		if (value == '-') { ++dash_count; }
		if (col == 9) { ++row; col = 1; }
		else { ++col; }
	}

	create_clusters();
	initial_shoop();
	fIn.close();
	
}
Board::~Board() {
	for (Cluster* x : bClusts) {
		delete x;
	}
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
	else { cout << dash_count << " empty spaces left." << endl; return false; }
}
//-------------------------------------------------------------------------
void Board::restore_state(BoardState* bs) {
	State* states = bs->getStates();
	for (int k = 0; k < BOARD_SIZE; ++k) {
		(State&)board[k] = states[k];
	}
	this->dash_count = bs->get_dash_count();
}
//-------------------------------------------------------------------------
ostream & Board::save_game(ofstream& fOut) {
	fOut << "t\n";
	for (short k = 0; k < BOARD_SIZE; ++k) {
		fOut << board[k].getValue();
		if (((k + 1) % 9) == 0) {
			fOut << "\n";
		}
	}
	return fOut;
}
//-------------------------------------------------------------------------
char Board::getMarkChar(int row, int col) const {
	// sub to find index
	int loc = sub(row, col);
	return board[loc].getValue();
}
//-------------------------------------------------------------------------
string Board::getPossibilityString(int row, int col) const {
	int loc = sub(row, col);
	short poss = board[loc].getPossibilities();
	string possibilities = "";

	for (int k = 9; k >= 1; k--) {
		int bit = poss & 1 << k;
		if (bit) { possibilities += k + '0'; }
		else { possibilities += '-'; }
	}
	return possibilities;
}
//-------------------------------------------------------------------------
void Board::create_clusters() {
	// clusters[27] - To store created clusters.
	// board[81]. Use these to create clusters.

	build_cl_row(); // Build Row Clusters: 0 - 8
	build_cl_col();	// Build Column Clusters: 9 - 17
	build_cl_blk();	// Build Block Clusters: 18 - 27
}
//-------------------------------------------------------------------------
void Board::build_cl_row() {
	// Outer iterates through to create n Clusters based on col size.
	// Inner gets the 9 relevant squares related to a persistent index (s).

	Square* cl_squares[9]; // Squares to be assigned to cluster.
	int board_i = 0;

	for (int ci = 0; ci < 9; ++ci) { // Creates Clusters
		for (int k = 0; k < 9; ++board_i, ++k) { // Gathers Squares
			cl_squares[k] = &board[board_i];
		}
		Cluster* temp = new Cluster(ROW, cl_squares);
		bClusts.push_back(temp);

	}
}
//-------------------------------------------------------------------------
void Board::build_cl_col() {
	// See build_cl_row() for general description.
	// col_start persists to help iterate through columns.
	// board_i will pick up where the previous inner op ended.

	Square* cl_squares[9]; // Squares to be assigned to cluster.
	int col_start = 0, board_i;

	for (int ci = 9; ci < 9 * 2; ++ci) { // Creates Clusters
		board_i = col_start;
		for (int k = 0; k < 9; ++k, board_i += 9) {
			cl_squares[k] = &board[board_i];
		}
		++col_start; // 1,1 -> 1,2 -> 1,3 etc. Change columns/starting point.
		Cluster* temp = new Cluster(COL, cl_squares);
		bClusts.push_back( temp );

	}
}
//-------------------------------------------------------------------------
void Board::build_cl_blk() {
	// See build_cl_row() for general description.
	// Creates 3x3 block clusters starting with 1,1.
	// Once it hits the last block in a row (ex. 3 out of 3 on size 9.
	// It recognizes and increments the board index to skip the next two rows.
	// Otherwise, there would be overlapping blocks.
	Square* cl_squares[9]; // To be assigned to cluster.
	int blk_start = 0, board_i;

	for (int ci = 9 * 2; ci < 9 * 3; ++ci) { // Creates Clusters.
		board_i = blk_start;
		for (int k = 0; k < 9; ++k) {
			cl_squares[k] = &board[board_i];
			if (!((board_i + 1) % 3) ) {
				board_i += (9 + 1) - 3;
			}
			else { ++board_i; }
		}
		if (!((1 + ci) % 3)) { blk_start += 3 * 7; }
		else { blk_start += 3; }


		Cluster* temp = new Cluster(BLK, cl_squares);
		bClusts.push_back(temp);

	}
}
//-------------------------------------------------------------------------
void Board::initial_shoop() {
	// Once the board has been constructed, use this to 'initialize'
	// All of the possibilities lists in each Square by Cluster.
	char value;
	for (int k = 0; k < BOARD_SIZE; ++k) {
		value = board[k].getValue();
		if (isdigit(value) ) { board[k].move(value); }
	}
}
//-------------------------------------------------------------------------
int Board::sub(int row, int col) const {
	// Algorithm that determines loc in array based on coordinates.
	int loc = (row - 1) * 9 + (col - 1);
	return loc;
}
//-------------------------------------------------------------------------
bool Board::move(int row, int col, char value) {
	int loc = sub(row, col);
	// If coordinates exceed the board:
	if (row > 9 || col > 9) { 
		say("Error: Coordinates exceed board size.");
		return false;
	}
	if (!board[loc].isFixed()) { // Is it a fixed Square?
		if (isdigit(value)) { // A numerical entry?
			if(!board[loc].validate_move(value)) { 
				board[loc].move(value);
				--dash_count;
				return true;
			}
			else { say("Error: Illegal move."); return false; }
		}
		else if (value == '-') { // A dash entry?
			board[loc].erase();
			++dash_count;
			return true;
		}
		else { say("Error: Value must be a number or dash."); return false; }
	}
	else { say("Error: Square is fixed. Cannot change values."); return false; }
}
//-------------------------------------------------------------------------
State Board::get_square(int square_loc) const {
	// Returns one whole Square from Board's array of Squares.
	// To be stripped and used to create a BoardState obj.
	//cout << "Getting Square: " << square_loc << endl; // DEBUG
	return board[square_loc];
}
//-------------------------------------------------------------------------
ostream & Board::print(ostream& out) {
	for (short k = 0; k < BOARD_SIZE; ++k) {
		board[k].print(out);
	}
	return out;
}
//-------------------------------------------------------------------------
/*---------This is the end of Board and the beginning of Diag. Board------*/
//-------------------------------------------------------------------------
Diagonal_Board::Diagonal_Board(const char* filename) {
	const char* printT[] = { "Row", "Column", "Block", "Diagonal" };
	string new_value;
	char value;
	short row = 1;
	short col = 1;
	dash_count = 0;
	string junk;

	say("Creating Diagonal Board");

	fIn.open(filename);
	fIn >> junk; // get the d

	// Read and construct a board using the passed file. Ex. 9x9 = 81 Sq's
	// First line will feature the puzzle type. ( (t)raditional, (d)iagonal
	// The following 9 are the puzzle.
	for (short k = 0; k < BOARD_SIZE; ++k) {
		fIn >> ws;
		value = fIn.get();
		if (fIn.eof()) { break; }
		board[k] = Square(value, row, col);
		if (value == '-') { ++dash_count; }
		if (col == 9) { ++row; col = 1; }
		else { ++col; }
	}
	Board::create_clusters();
	Diagonal_Board::create_clusters();
	Board::initial_shoop();
	fIn.close();
}
//-------------------------------------------------------------------------
void Diagonal_Board::create_clusters() {
	// For continuity with traditional board function structure.
	// This only has to call the diagonal cluster function.
	build_cl_diag1(); // Build Block Cluster 28. Top Down.
	build_cl_diag2(); // Build Block Cluster 29. Bottom Up.
}
//-------------------------------------------------------------------------
void Diagonal_Board::build_cl_diag1() {
	// In addition to traditional board clusters, diagonal boards also
	// need two additional clusters: 1,1 to 9,9 and 1,9 to 9,1.
	Square* cl_squares[9]; // Squares to be assigned to cluster.

	// 1,1 to 9,9, diagonally
	for (int k = 0, board_i = 0; k < 9; ++k) {
		cl_squares[k] = &board[board_i];
		board_i = board_i + 10;
	}
	Cluster* temp = new Cluster(DIA, cl_squares);
	bClusts.push_back(temp);


}
//-------------------------------------------------------------------------
void Diagonal_Board::build_cl_diag2() {
	// In addition to traditional board clusters, diagonal boards also
	// need two additional clusters: 1,1 to 9,9 and 1,9 to 9,1.
	Square* cl_squares[9]; // Squares to be assigned to cluster.
	int board_i = 9;

	// 1,9 to 9,1 diagonally
	for (int k = 0, board_i = 8; k < 9; ++k) {
		cl_squares[k] = &board[board_i];
		board_i = board_i + 8;
	}

	Cluster* temp = new Cluster(DIA, cl_squares);
	bClusts.push_back(temp);


}
//-------------------------------------------------------------------------
ostream & Diagonal_Board::save_game(ofstream& fOut) {
	fOut << "d\n";
	for (short k = 0; k < BOARD_SIZE; ++k) {
		fOut << board[k].getValue();
		if (((k + 1) % 9) == 0) {
			fOut << "\n";
		}
	}
	return fOut;
}
//-------------------------------------------------------------------------