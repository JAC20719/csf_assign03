#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

using std::vector;
class Block {
public:
  vector<unsigned> block{0, 0, 0};
	// my thought is to store [tag, valid, order]
  Block() {
    //All blocks invalid upon creation
    
  } 

	// on piazza he said we didn't need to store the actual data
	// because its a simulation



	// destructor (do we need this?)
	~Block();

	// define functions to manipulate block below
	void toString();

	unsigned getTag();

	unsigned getValid();

	unsigned getOrder();
	
};

#endif // BLOCK_H
