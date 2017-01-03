#include "Square.hpp"
// On input file read:
// Dashed values (or zeroes) are moved in and may be changed.
// Non-zero digits are moved in and may not be changed.
// Everything else is ignored or caught. Default solution = dash.
State::~State() {
	//cerr << "State destroyed." << endl;
}
//-------------------------------------------------------------------------
void State::move(char ch) {
	if (isdigit(ch))  {
		if (ch != '0') {
			if (!fixed) {
				cout << "Placing " << ch << "." << endl;
				value = ch;
			}
		}
		else { cout << "Error: Input. Try again." << endl; }
	}
	if (value == '-') {
		if (!fixed) {
			cout << "Placing dash." << endl;
			value = '-';
		}
	}
}
//-------------------------------------------------------------------------
void State::erase() {
	if (fixed == false) {
		say("Erasing input."); value = '-'; return;
	}
	say("Cannot erase fixed square.");
}
//-------------------------------------------------------------------------
ostream& State::print(ostream& out) {
	out << "Value: " << value;
	out << "  Fixed: " << fixed;
	out << "  Poss. List: ";
	for (int k = 1; k <= 9; ++k) {
		int bit = MASK & possibilities >> k;
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
Square::Square(char ch, short int row, short int col) : State() {
	//cerr << "Square [" << row << ", " << col << "] constructed." << endl;
	State::move(ch);
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
ostream& Square::print(ostream& out) {
	out << "[" << row << ", " << col << "]\t";
	State::print(out);
	return out;
}
//-------------------------------------------------------------------------
void Square::move(char ch) {
	State::move(ch);
}
//-------------------------------------------------------------------------