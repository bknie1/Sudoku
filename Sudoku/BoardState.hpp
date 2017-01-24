#pragma once
#include "Tools.hpp"
#include "Square.hpp"
#define BOARD_SIZE 81

class Board;

//-------------------------------------------------------------------------
// BoardState - Stores 'versions' of the Board for the undo/redo stacks.
class BoardState {
private:
	State states[BOARD_SIZE];
public:
	BoardState(const Board* bd);
	~BoardState() = default;
	ostream& print(ostream& out);
};

inline ostream& operator<< (ostream& out, BoardState bs) {
	// cout << bs << endl;
	bs.print(out);
	return out;
}
//-------------------------------------------------------------------------
// Stack - Undo and Redo stacks of BoardState.
class Stack : public vector<BoardState*> {
public:
	Stack() = default;
	~Stack() = default;
	void pop();
	inline void push(BoardState* bs) { this->push_back(bs); }
	inline BoardState* top() { return this->back(); }
	inline int size() { return vector::size(); }
	// use the :: operator to call the size() function from the base class. 
	// (Otherwise, an attempt to delegate becomes an infinite recursion and
	// your program will end with a segmentation error.
	inline void zap() { for (int k = 0; k < size(); ++k) { pop(); } } // Empty
};