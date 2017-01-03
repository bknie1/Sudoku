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