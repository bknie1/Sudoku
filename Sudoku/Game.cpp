#include "Game.hpp"

Game::Game() {
	// Creates a board of BOARD_SIZE squares from a validated input file.
	try {
		char type;
		ifstream fIn;
		fIn.open(file_name);
		if (!fIn.is_open()) throw StreamException();
		fIn >> ws;
		type = fIn.get();
		if (type == 't') {
			board = new Board(file_name);
		}
		else if (type == 'd') {
			board = new Diagonal_Board(file_name);
		}
		else { cout << "Error: Unrecognized type." << endl; }
		fIn.close();
	}
	catch (StreamException& e) {
		e.print(cerr);
		return;
	}
}
//-------------------------------------------------------------------------
void Game::run() {
	// Print the Board, Menu, and an actions menu.
	char sel;
	int row;
	int column;
	char value;
	const char* menu[] = { 
		"(M)ove", "(U)ndo", "(R)edo", "(S)ave", "(L)oad", "(Q)uit"
	};
	string valid = "murslq";

	Viewer fancyView(9, 9, *board);
	
	for (;;) {
		// Returns true? There are no more dashes/all spots filled.
		if (board->is_done()) { break; }
		board->print(cout);
		fancyView.show(cout);

		sel = menu_c("\t      Sudoku Menu", 6, menu, valid);

			switch (sel) {
			case 'm': // Move
				cout << "Input (Row) (Column) (Value): ";
				cin >> row; cin >> column; cin >> value;
				board->move(row, column, value);
				break;
			case 'u': // Undo

				break;
			case 'r': // Redo

				break;
			case 's': // Save Game

				break;
			case 'l': // Restore Game

				break;
			case 'q': // Quit and Discard Game
				delete board;
				return;
			default:
				say("Error: Invalid input.");
				break;
			}
		}
	say("Congratulations, you've won!");
}
// ----------------------------------------------------------------------------
// Display a menu then read an alphabetic menu choice character.
// Supply a title, the number of menu choices, an array of const char* 
// for the options, and a const char* c - string that lists the first 
// letter of each legal choice.

char Game::menu_c(const char* title, int n, const char* menu[], const string valid) {
	int k;
	char choice;
	for (;;) {
		cout << endl << title << endl << endl;
		for (k = 0; k < n; ++k) cout << "\t     - " << menu[k] << endl;
		cout << endl << " Enter code of desired item: ";
		cin >> choice;
		cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
		choice = tolower(choice);
		if (valid.find_first_of(choice) != string::npos)  break;
		cout << " Please enter a valid choice from the menu.\n\n";
	}
	return choice;
}