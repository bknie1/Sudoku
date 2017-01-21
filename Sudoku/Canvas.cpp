/*
 * Canvas.cpp
 *
 *  Created on: Oct 27, 2012
 *      Author: mike
 */

#include <iostream>
using namespace std;

#include "Canvas.hpp"

Canvas::Canvas(int nr, int nc) :
		height(nr), width(nc) {
	pixel = new MixedChar[nr * nc];
}

Canvas::~Canvas() {
	delete[] pixel;
}

void Canvas::show(ostream& out) {
	for (int sr = 0; sr < height; ++sr) {
		for (int sc = 0; sc < width; ++sc)
			out << sub(sr, sc);
		cout << endl;
	}
}

