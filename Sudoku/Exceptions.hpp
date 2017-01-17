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

inline ostream& operator<< (ostream& out, StreamException& s) { return out; }
inline ostream& operator<< (ostream& out, LogicException& l) { return out; }