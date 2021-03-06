#include "Game.hpp"

Game::Game() {
	// Creates a board of BOARD_SIZE squares from a validated input file.
	load_menu();
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
	delete board;
}
//-------------------------------------------------------------------------
void Game::run() {
	// Print the Board, Menu, and an actions menu.
	char sel;
	string file_name;
	const char * file;

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
				cout << "Save file name: "; cin >> file_name;
				file = file_name.c_str();
				save_game(file);
				break;
			case 'l': // Restore Game
				cout << "Load file name: "; cin >> file_name;
				file = file_name.c_str();
				load_game(file);
				break;
			case 'q': // Quit and Discard Game
				return;
			default:
				say("Error: Invalid input.");
				break;
			}
		}
	say("Congratulations, you've won! Thanks for playing.");
}
//-------------------------------------------------------------------------
void Game::load_menu() {
	char sel;
	string file_name;
	const char * file;

	cout << "\t- Load (N)ew Game from a Text File (*.txt)" << endl;
	cout << "\t- Load (S)aved Game from a Binary File (*.bin)" << endl;
	cout << "\t- (Q)uit" << endl;
	cout << "Selection: ";

	cin >> sel;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	sel = tolower(sel);

	switch (sel) {
	case 'n': load_new_game(); break;
	case 's': cout << "Load file name: "; cin >> file_name;
			  file = file_name.c_str();
			  load_game(file);
			  break;
	case 'q': exit(1);
	default: say("Error: Invalid selection."); exit(1);
	}
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
void Game::save_game(const char* output_file) {
	try {
		BoardState* top = undo.top();
		ofstream fOut(output_file, ios::binary);
		if (!fOut.is_open()) throw StreamException();
		top->serialize(fOut);
		fOut.close();
	}
	catch (StreamException &e) {
		e.print(cerr);
	}
}
//-------------------------------------------------------------------------
void Game::load_game(const char* input_file) {
	try {
		board = new Board();
		BoardState* first_bs = new BoardState();
		cout << "Loading file: " << input_file << endl;
		ifstream fIn(input_file, ios::binary);
		if (!fIn.is_open()) throw StreamException();
		first_bs->realize(fIn);
		undo.zap();// Clear the way for a fresh game.
		redo.zap();
		undo.push(first_bs); // The first BoardState, loaded from the file.
		board->restore_state(undo.top());
		fIn.close();
	}
	catch (StreamException &e) {
		e.print(cerr);
	}
}
//-------------------------------------------------------------------------
void Game::load_new_game() {
	for (;;) {
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
			fIn.close();
			if (type == 't') {
				board = new Board(file);
				BoardState* bs = new BoardState(board);
				undo.push(bs);
				break;
			}
			else if (type == 'd') {
				board = new Diagonal_Board(file);
				BoardState* bs = new BoardState(board);
				undo.push(bs);
				break;
			}
			else { cout << "Error: Unrecognized type." << endl; }
		}
		catch (StreamException& e) {
			e.print(cerr);
		}
	}
}
//-------------------------------------------------------------------------