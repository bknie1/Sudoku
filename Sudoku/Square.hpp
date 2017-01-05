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
#define MASK 0x7fe // 011111111110
// Forward declaration for the Square/Cluster circular include.
#include "Cluster.hpp"
class Cluster;

class State {
protected:				// Only visible to Square.
	char value = '-';	// Contents of the square at any given time.
	short possibilities = MASK;	// Possibilities list.
	bool fixed = false;	// T: Read from input file. F: Modifiable.
public:
	State() = default;
	~State();
	void move(char ch);	// Assign value to State.
	void turn_off(char ch); // Turns a value off.
	void erase();		// Erase the value of State.
	void turn_on(char ch); // Turns a value on.
	ostream& print(ostream& out);	// Print possibilities in values/dashes.
};
//-------------------------------------------------------------------------
class Square : public State {
protected:
	short int row;
	short int col;
	vector<Cluster*> clues;
	short int poss_count; // Possibilities count.
public:
	Square();
	Square(char dd, short int row, short int col);	// Ctor into State.
	~Square();
	ostream& print(ostream&);
	void move(char ch);  // Writes submission.
	inline void addCluster(Cluster* c) { clues.push_back(c); }
	inline int getRow() { return row; }
	inline int getCol() { return col; }
};
inline ostream& operator<< (ostream& out, Square& sq) { return out; }
