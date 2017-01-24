#include "BoardState.hpp"
#include "Board.hpp"

//-------------------------------------------------------------------------
BoardState::BoardState(const Board* board) {
	for (int sq_loc = 0; sq_loc < 81; ++sq_loc) {
		states[sq_loc] = board->get_square(sq_loc);
		//states[sq_loc].print(cout);// DEBUG
	}
}
//-------------------------------------------------------------------------
void Stack::pop() {
	BoardState* bs = top();
	vector::pop_back();
}
//-------------------------------------------------------------------------
ostream & BoardState::print(ostream & out) {
	cout << "Print BoardState" << endl;
	return out;
}