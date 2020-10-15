#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
using std::vector;

class Block {

public:
	vector<int> block;
	// my thought is to store [tag, valid, order]
	Block(): block(3){} 

	// on piazza he said we didn't need to store the actual data
	// because its a simulation



	// destructor (do we need this?)
	~Block();

	// define functions to manipulate block below
};

#endif // BLOCK_H
