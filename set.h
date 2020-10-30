#ifndef SET_H
#define SET_H

#include <vector>
#include "block.h"

using std::vector;
class Set {
 private:
  int long unsigned index; 
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

	void toString();
	long unsigned getIndex();
    
};

#endif // SET_H
