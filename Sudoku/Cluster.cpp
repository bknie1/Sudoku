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
bool Cluster::check_cluster(char value) {
	// Determines if there's a value conflict in the cluster.
	for (int k = 0; k < MAX_COL; ++k) {
		cout << "Comparing " << value << " and " << cl_squares[k]->getValue() << endl;
		if (value == cl_squares[k]->getValue()) {
			cout << "Conflict between " << value << " and " << cl_squares[k]->getValue() << endl;
			return true; // Conflict?
		}
	}
	cerr << "Valid value for shoop()" << endl;
	return false;
}
//-------------------------------------------------------------------------
void Cluster::shoop(char value) {
	cout << "Shooping " << value << "." << endl;
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
	out << "\Cluster Type: " << printT[name] << endl;
	for (int k = 0; k < MAX_COL; ++k) {
		cl_squares[k]->print(out);
	}
	out << endl;
	return out;
}
//-------------------------------------------------------------------------