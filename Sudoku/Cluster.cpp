#include "Cluster.hpp"

Cluster::Cluster(clusterT name, Square* cl_squares[]) {
	this->name = name;
	for (int k = 0; k < MAX_COL; ++k) {
		this->cl_squares[k] = cl_squares[k];
	}
}
//-------------------------------------------------------------------------
Cluster::Cluster() {
}
//-------------------------------------------------------------------------
Cluster::~Cluster() {
}
//-------------------------------------------------------------------------
void Cluster::shoop(char value) {
	//cout << "Shooping " << value << "." << endl; // DEBUG
	for (int k = 0; k < MAX_COL; ++k) {
		cl_squares[k]->turn_off(value);
	}
}
//-------------------------------------------------------------------------
ostream& Cluster::print(ostream& out) {
	// I wanted to use the printT from board but had to do this.
	// Why wouldn't printT just exist here because Cluster is
	// in charge of printing itself? Isn't it supposed to be?
	string printT[] = { "Row", "Column", "Block" };
	out << "Cluster Type: " << printT[name] << endl;
	for (int k = 0; k < MAX_COL; ++k) {
		cl_squares[k]->print(out);
	}
	out << endl;
	return out;
}
//-------------------------------------------------------------------------