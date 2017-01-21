/*
 * CanView.hpp
 *
 *  Created on: May 15, 2014
 *      Author: mike
 */

// Interface class for a viewable Sudoku model

#ifndef CANVIEW_HPP_
#define CANVIEW_HPP_

#include <string>
using namespace std;

class CanView {
public:
	virtual ~CanView() {};
	virtual char getMarkChar(int row, int col) const =0;
	virtual string getPossibilityString(int row, int col) const =0;

};

#endif /* CANVIEW_HPP_ */
