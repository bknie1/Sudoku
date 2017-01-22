#include "BoardState.hpp"

//-------------------------------------------------------------------------
BoardState::BoardState(Board &bd) {
	memcpy(&board, &bd, sizeof(bd));
}
//-------------------------------------------------------------------------
ostream & BoardState::print(ostream & out) {
	board.print(out);
	return out;
}
//-------------------------------------------------------------------------