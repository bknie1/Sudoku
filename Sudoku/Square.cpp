#include "Square.hpp"
// On input file read:
// Dashed values (or zeroes) are moved in and may be changed.
// Non-zero digits are moved in and may not be changed.
// Everything else is ignored or caught. Default solution = dash.
State::~State() {
	//cerr << "State destroyed." << endl;
}
//-------------------------------------------------------------------------
void State::move(char value) {
	if (fixed == false) {
		if (isdigit(value) ) {
			this->value = value;
			turn_off(value); // Remove new val. from poss. list.
		}
		else { cout << "Error: Input. Try again." << endl; }
	}
}
//-------------------------------------------------------------------------
void State::erase() {
	if (fixed == false) {
		turn_on(value); // Toggles the previous value back on.
		value = '-'; return;
	}
	say("Cannot erase fixed square.");
}
//-------------------------------------------------------------------------
void State::turn_off(char ch) {
	/* We want to shift the third bit. Shift a single '1' over 3 bits:
		000000100
	Now, we have to invert it with a NOT:
		111111011
	Assuming everything is possible right now:
		111111111 <- Everything is on.
	&	111111011 <- We created that mask to isolate '3'.
		---------
		111111011 <- Clear anything marked 0. 3 is now 0.
	*/
	int n = ch - '0';
	possibilities = possibilities & ~(1 << n);
	//print_bin(possibilities); // Debugging
}
//-------------------------------------------------------------------------
void State::turn_on(char old_value) {
	// TODO use this and shoop() to turn back on all values.
	int old = old_value - '0';
	possibilities = possibilities | 1 << old;
	//print_bin(possibilities); // Debugging
	/*		111111011 <- '3' is toggled off.
		|	000000100 <- Mask to isolate '3'. | to set it.
			---------
			111111111 <- '3' is back on!
	*/
}
//-------------------------------------------------------------------------
void State::print_bin(unsigned short possibilities) {
	for (int i = 9; i >= 0; i--) {
		if (possibilities & (1 << i)) { cout << 1; }
		else { cout << 0; }
	}
	cout << endl;
}
//-------------------------------------------------------------------------
ostream& State::print(ostream& out) {
	out << "Value: " << value;
	if (fixed) { out << "  Fixed: true "; }
	if (!fixed) { out << "  Fixed: false"; }
	out << "  Possibilities: ";
	for (int k = 9; k >= 1; k--) {
		int bit = possibilities & 1 << k;
		if (bit) { cout << k; }
		else { cout << '-'; }
	}
	cout << endl;
	return out;
}
//-------------------------------------------------------------------------
/*---------This is the end of State and the beginning of Square.---------*/
//-------------------------------------------------------------------------
// Square is the physical representation of the State/Square
// relationship on the board. Board is comprised of 81 squares (9x9).
Square::Square(char value, short row, short col) : State() {
	if (isdigit(value)) {
		this->value = value;
		this->row = row;
		this->col = col;
		fixed = true; // Only occurs on puzzle file read.
		possibilities = 0;
	}
	this->row = row;
	this->col = col;
}
//-------------------------------------------------------------------------
Square::Square() {
	//cerr << "An empty Square was constructed." << endl;
}
//-------------------------------------------------------------------------
Square::~Square() {
	//cerr << "Destroying Square [" << row << ", " << col << "]" << endl;
}
//-------------------------------------------------------------------------
void Square::move(char new_value) {
	// Adjusts neighbor Squares via Cluster's shoop. Must be a digit.
	char old_value = value;
	value = new_value;
	if (fixed) { possibilities = 0; }
	for (unsigned short k = 0; k < clues.size(); ++k) {
		if (isdigit(new_value)) {
			clues[k]->shoop_off(new_value);
		}
	}
}
	//cout << clues.size() << endl; // DEBUG
	//print_clues(cout); // DEBUG
	//cout << "Considering " << value << endl; // DEBUG
	//cout << "This is Square " << row << ", " << col << endl; // DEBUG
//-------------------------------------------------------------------------
void Square::erase() {
	// The user entered a dash indicating erasure.
	// Turn old value back on for all neighboring Squares.
	// This Square is assigned a dash.
	for (int k = 0, s = clues.size(); k < s; ++k) {
		clues[k]->shoop_on(value);
	}
	value = '-';
}
//-------------------------------------------------------------------------
ostream & Square::print_clues(ostream & out) {
	State::erase();
	for (int k = 0, s = clues.size(); k < s; ++k) {
		clues[k]->print(out);
	}
	return out;
}
//-------------------------------------------------------------------------
ostream& Square::print(ostream& out) {
	out << "[" << row << ", " << col << "]\t";
	State::print(out);
	return out;
}
//-------------------------------------------------------------------------