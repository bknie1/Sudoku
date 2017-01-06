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
				turn_off(value); // Remove new val. from poss. list.
			}
		}
		else { cout << "Error: Input. Try again." << endl; }
	}
	if (ch == '-') {
		if (!fixed) {
			cout << "Placing dash." << endl;
			if (isdigit(value)) { turn_on(value); }// Add old val. back to poss. list.
			value = '-';
		}
	}
}
//-------------------------------------------------------------------------
void State::erase() {
	if (fixed == false) {
		turn_on(value); // Toggles the previous value back on.
		say("Erasing input."); value = '-'; return;
	}
	say("Cannot erase fixed square.");
}
//-------------------------------------------------------------------------

void State::turn_off(char ch) {
	int n = ch - '0'; // Char to int.
	int mask = 0x3fe;
	cout << "Shifting " << n << " times." << endl; // DEBUG
	cout << bitset<10>(possibilities) << endl; // DEBUG
	//possibilities ^=  (~mask) << (n - 1) & possibilities;
	possibilities &= (~mask) & possibilities;
	cout << bitset<10>(possibilities) << endl; // DEBUG
}
//-------------------------------------------------------------------------

void State::turn_on(char ch) {
	//(~MASK) & possibilities |= << n;
}
//-------------------------------------------------------------------------
ostream& State::print(ostream& out) {
	out << "Value: " << value;
	if (fixed) { out << "  Fixed: true "; }
	if (!fixed) { out << "  Fixed: false"; }
	//out << "  Fixed: " << fixed;
	out << "  Possibilities: ";
	for (int k = 1; k <= 9; ++k) {
		int bit = 0x3 & possibilities >> k;
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
	if (isdigit(ch)) { 
		fixed = true; // Only occurs on puzzle file read.

	}
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