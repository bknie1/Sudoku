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

// Forward declaration for the Square/Cluster circular include.
#include "Cluster.hpp"
class Cluster;

class State {
protected:				// Only visible to Square.
	char value = '-';	// Contents of the square at any given time.
	bool fixed = false;	// T: Read from input file. F: Modifiable.
	unsigned short possibilities = ~0;
	void print_bin(unsigned short possibilities);
public:
	State() = default;
	~State();
	void move(char ch);	// Assign value to State.
	void turn_off(char ch); // Turns a value off.
	void erase();		// Erase the value of State.
	void turn_on(char ch); // Turns a value on.
	bool validate_move(char ch); // Is a move legal? Refer to poss list.
	ostream& print(ostream& out);	// Print possibilities in values/dashes.

	inline short getPossibilities() const { return possibilities; }
	inline bool isFixed() {if(fixed) {return true;} else {return false;}}
};
//-------------------------------------------------------------------------
class Square : public State {
protected:
	short int row;
	short int col;
	vector<Cluster*> clues; // Should contain 3-4 Clusters.
public:
	Square();
	Square(char ch, short row, short col);	// Ctor into State.
	~Square();
	void move(char value);  // Writes submission.
	inline void addCluster(Cluster* c) { clues.push_back(c); }
	inline char getValue() const { return value; }
	inline vector<Cluster*> getClues() { return clues; }
	inline short getRow() { return row; }
	inline short getCol() { return col; }
	void erase();
	ostream& print_clues(ostream& out);
	ostream& print(ostream& out);
};
inline ostream& operator<< (ostream& out, Square& sq) {
	// cout << sq << endl;
	sq.print(out);
	return out;
}