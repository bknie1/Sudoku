/*	Program: Sudoku
Description: A simple, console-based C++ implementation of a
9x9 Sudoku board game. See Sudoku.cpp or the Readme for more.
*/

/*	Class Description: Cluster is used to toggle possibilities for
	each Square surrounding a given Square in order to provide
	clues for the player.
*/

#pragma once
#include "tools.hpp"
#include "Square.hpp"

#define MAX_COL 9	// Max column/row size. Used to adjust coords.

class Square;

enum clusterT;

class Cluster {
private:
	clusterT name;
	Square* cl_squares[9];
public:
	Cluster(clusterT type, Square* cl_squares[]);
	Cluster();
	~Cluster();
	bool check_cluster(char value);
	void shoop(char ch); // Removes possibility from each cluster.
	ostream& print(ostream& out);
};