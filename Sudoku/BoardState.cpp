#include "BoardState.hpp"
#include "Board.hpp"

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

void Stack::pop() {
	BoardState* bs = top();
	vector::pop_back();
	delete bs;
}

ostream & BoardState::print(ostream & out) {
	cout << "Print BoardState" << endl;
	return out;
}
