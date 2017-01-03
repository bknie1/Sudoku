/*	Program: Sudoku
	Description: A simple, console-based C++ implementation of a
	9x9 Sudoku board game. See Sudoku.cpp or the Readme for more.
*/

/*	Class Description: Square handles the physical nature of it's
	interactions with the Sudoku board. Square is derived from State.
	State is more logical in nature; it contains data about the Square.
	If the Square is what you see on the board State is what you're
	actually 'writing' on.
*/

#pragma once
#include "Tools.hpp"
#define MASK 0x7fe

class State {
protected:				// Only visible to Square.
	char value = '-';	// Contents of the square at any given time.
	short possibilities = MASK;	// Possibilities list.
	bool fixed = false;	// T: Read from input file. F: Modifiable.
public:
	State() = default;
	~State();
	void move(char ch);	// Assign value to State.
	void erase();		// Erase the value of State.
	ostream& print(ostream& out);	// Print possibilities in values/dashes.
};