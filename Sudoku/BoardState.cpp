#include "BoardState.hpp"
#include "Board.hpp"

//-------------------------------------------------------------------------
BoardState::BoardState(const Board* board) {
	for (int sq_loc = 0; sq_loc < 81; ++sq_loc) {
		states[sq_loc] = board->get_square(sq_loc);
	}
	dash_count = board->get_dash_count();
}
//-------------------------------------------------------------------------
void Stack::pop() {
	BoardState* bs = top();
	vector::pop_back();
}
//-------------------------------------------------------------------------
ostream & BoardState::print(ostream & out) {
	for (int sq_loc = 0; sq_loc < 81; ++sq_loc) {
		states[sq_loc].print(cout);
	}
	return out;
}
//-------------------------------------------------------------------------
void BoardState::serialize(ostream & out) {
	out.write((char *)&dash_count, sizeof((dash_count)));
	out.write((char *)&states, sizeof(states));
}
//-------------------------------------------------------------------------
void BoardState::realize(istream & in) {
	in.read((char *)&dash_count, sizeof((dash_count)));
	in.read((char *)&states, sizeof(states));
}
//-------------------------------------------------------------------------