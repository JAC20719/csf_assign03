#ifndef SET_H
#define SET_H

#include <vector>
#include "block.h"

using std::vector;
class Set {
 private:
  int long unsigned index; //Should this be long unsigned for if index > 32 bits??
  int blocks_per_set;
public:
	vector<Block> set;
	
	Set(int bps, int i) {
	  blocks_per_set = bps;
	  index = i;

	  for(int i = 0; i < blocks_per_set; i++) {
	    set.push_back(Block());
	  }
	}

	// Destructor (do we need this?)
	~Set();

	// Add functions to manipulate set
	void toString();
	
	long unsigned getIndex();
    
};

#endif // SET_H
