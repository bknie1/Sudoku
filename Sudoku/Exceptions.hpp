#pragma once
#include "Tools.hpp"

class StreamException : public exception {
public:
	StreamException();
	ostream& print(ostream& out);
};

class LogicException : public exception {
public:
	LogicException();
	ostream& print(ostream& out);
};

inline ostream& operator<< (ostream& out, StreamException& se) {
	// cout << se << endl;
	se.print(out);
	return out;
}
inline ostream& operator<< (ostream& out, LogicException& le) {
	// cout << le << endl;
	le.print(out);
	return out;
}