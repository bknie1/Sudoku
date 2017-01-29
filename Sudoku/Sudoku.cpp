/*	Program: Sudoku
	Description: A simple, console-based C++ implementation of a
	9x9 Sudoku board game.
	Header/Source Files: Sudoku.cpp, Tools.hpp/cpp, Square.hpp/cpp,
	Board.hpp/cpp, Cluster.hpp/cpp, Exceptions.hpp/cpp, CanView.hpp,
	Viewer.hpp/cpp, Canvas.hpp/cpp, GridChar.hpp/cpp, MixedChar.hpp/cpp
*/
#include "Game.hpp"
//#define _CRTDBG_MAP_ALLOC  
//#include <stdlib.h>
//#include <crtdbg.h>
//-------------------------------------------------------------------------
int main() {
	cout << "\t    SUDOKU\n" << endl;
	Game g;
	g.run();
	//_CrtDumpMemoryLeaks();
}
//-------------------------------------------------------------------------