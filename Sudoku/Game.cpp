#include "Game.hpp"

Game::Game() {
	// Creates a board of BOARD_SIZE squares from a validated input file.
	load_game();
}
//-------------------------------------------------------------------------
Game::~Game() {
	for (int k = 0; k < undo.size(); ++k) {
		delete undo.top();
		undo.pop();
	}
	for (int k = 0; k < redo.size(); ++k) {
		delete redo.top();
		redo.pop();
	}
}
//-------------------------------------------------------------------------
void Game::run() {
	// Print the Board, Menu, and an actions menu.
	char sel;

	const char* menu[] =
	{ "(M)ove", "(U)ndo", "(R)edo", "(S)ave", "(L)oad", "(Q)uit" };
	string valid = "murslq";

	Viewer fancyView(9, 9, *board);
	
	for (;;) {
		// Returns true? There are no more dashes/all spots filled.
		if (board->is_done()) { break; }
		// board->print(cout); // Prints the full contents of each Square.
		fancyView.show(cout);

		sel = menu_c("\t      Sudoku Menu", 6, menu, valid);

			switch (sel) {
			case 'm': // Move
				move();
				break;
			case 'u': // Undo
				undo_move();
				break;
			case 'r': // Redo
				redo_move();
				break;
			case 's': // Save Game
				save_game();
				break;
			case 'l': // Restore Game
				load_game();
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
//----------------------------------------------------------------------------
void Game::move() {
	int row;
	int column;
	char value;
	bool valid;
	cout << "Input (Row) (Column) (Value): ";
	cin >> row; cin >> column; cin >> value;
	valid = board->move(row, column, value);
	if (valid) {
		BoardState* bs = new BoardState(board);
		undo.push(bs);
	}
}
//-------------------------------------------------------------------------
void Game::undo_move() {
	if (undo.size() >= 2) {
		redo.push(undo.top());
		undo.pop();
		board->restore_state(undo.top());
	}
}
//-------------------------------------------------------------------------
void Game::redo_move() {
	if (redo.size() > 0) {
		board->restore_state(redo.top());
		undo.push(redo.top());
		redo.pop();
	}
}
//-------------------------------------------------------------------------
void Game::save_game() {
	try {
		string file_name;
		ofstream fOut;
		cout << "Enter a file name (without *.txt): "; cin >> file_name;
		file_name += ".txt";
		const char * file = file_name.c_str(); // String to const char*
		fOut.open(file);
		if (!fOut.is_open()) throw StreamException();
		board->save_game(fOut);
		fOut.close();
	}
	catch (StreamException& e) {
		e.print(cerr);
		return;
	}
}
//-------------------------------------------------------------------------
void Game::load_game() {
	try {
		char type;
		string file_name;
		ifstream fIn;
		cout << "Enter a file name (without *.txt): "; cin >> file_name;
		file_name += ".txt";
		const char * file = file_name.c_str(); // String to const char*
		fIn.open(file);
		if (!fIn.is_open()) throw StreamException();
		fIn >> ws;
		type = fIn.get();
		if (type == 't') {
			board = new Board(file);
		}
		else if (type == 'd') {
			board = new Diagonal_Board(file);
		}
		else { cout << "Error: Unrecognized type." << endl; }
		BoardState* bs = new BoardState(board);
 		undo.push(bs);
		fIn.close();
	}
	catch (StreamException& e) {
		e.print(cerr);
		return;
	}
}
//-------------------------------------------------------------------------