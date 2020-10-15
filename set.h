#ifndef SET_H
#define SET_H

#include <vector>
#include "block.h"
using std::vector;

class Set {

public:
	vector<Block> set;
	Set(int m): set(m){}

	// Destructor (do we need this?)
	~Set();

	// Add functions to manipulate set
};

#endif // SET_H
