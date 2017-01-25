#include "Cluster.hpp"

Cluster::Cluster(int name, Square* cl_squares[]) {
	this->name = name;
	for (int k = 0; k < MAX_COL; ++k) {
		this->cl_squares[k] = cl_squares[k];
		cl_squares[k]->addCluster(this);
	}
}
//-------------------------------------------------------------------------
void Cluster::shoop_off(char new_value) {
	for (int k = 0; k < MAX_COL; ++k) {
		cl_squares[k]->turn_off(new_value);
	}
}
//-------------------------------------------------------------------------
void Cluster::shoop_on(char old_value) {
	for (int k = 0; k < MAX_COL; ++k) {
		cl_squares[k]->turn_on(old_value);
	}
}
//-------------------------------------------------------------------------
ostream& Cluster::print(ostream& out) {
	// I wanted to use the printT from board but had to do this.
	// Why wouldn't printT just exist here because Cluster is
	// in charge of printing itself? Isn't it supposed to be?
	string printT[] = { "Row", "Column", "Block", "Diagonal" };
	out << "Cluster Type: " << printT[name] << endl;
	for (int k = 0; k < MAX_COL; ++k) {
		cl_squares[k]->print(out);
	}
	out << endl;
	return out;
}
//-------------------------------------------------------------------------