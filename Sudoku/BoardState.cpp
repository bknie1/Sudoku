#include "BoardState.hpp"
#include "Board.hpp"

//-------------------------------------------------------------------------
BoardState::BoardState(Board* bd) {
	memcpy(&board, &bd, sizeof(&bd));
}
//-------------------------------------------------------------------------
ostream& BoardState::print(ostream & out) {
	board.print(out);
	return out;
}
//-------------------------------------------------------------------------

void Stack::pop() {
	BoardState* bs = top();
	vector::pop_back();
	delete bs;
}