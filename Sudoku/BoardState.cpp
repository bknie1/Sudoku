#include "BoardState.hpp"
#include "Board.hpp"

//-------------------------------------------------------------------------
BoardState::BoardState(const Board* board) {
	for (int k = 0; k < 81; ++k) {
		states[k];
		board[k];
	}
}
//-------------------------------------------------------------------------
void Stack::pop() {
	BoardState* bs = top();
	vector::pop_back();
	delete bs;
}
//-------------------------------------------------------------------------
ostream & BoardState::print(ostream & out) {
	cout << "Print BoardState" << endl;
	return out;
}