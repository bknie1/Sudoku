#include "Exceptions.hpp"

//-------------------------------------------------------------------------

StreamException::StreamException() {
	
}
//-------------------------------------------------------------------------
ostream & StreamException::print(ostream & out) {
	out << "Error: File stream exception" << endl;
}
//-------------------------------------------------------------------------

LogicException::LogicException() {

}
//-------------------------------------------------------------------------
ostream & LogicException::print(ostream & out) {
	out << "Error: Game logic exception." << endl;
}
//-------------------------------------------------------------------------