#include "BoardState.hpp"
#include "Board.hpp"

//-------------------------------------------------------------------------
BoardState::BoardState(const Board* board) {
	for (int sq_loc = 0; sq_loc < 81; ++sq_loc) {
		states[sq_loc] = board->get_square(sq_loc);
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
//-------------------------------------------------------------------------
void BoardState::serialize(ostream & out) {
	try {
		out.write((char *)&states, sizeof(states)); throw StreamException();
	}
	catch (StreamException e) {
		e.print(cout);
	}
}
//-------------------------------------------------------------------------
void BoardState::realize(istream & in) {
	try {
		in.read((char *)&states, sizeof(states)); throw StreamException();
	}
	catch (StreamException e) {
		e.print(cout);
	}
}
//-------------------------------------------------------------------------