#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <vector>
#include "set.h"

using std::string;
class Cache {
 private:
  string write_miss = "";
  string write_hit = "";
  int num_sets;
 public:
  vector<Set> cache;
  
	// constructor
  Cache(int n, string wm, string wh) {
    num_sets = n;
    cache.push_back(num_sets);
    write_miss = wm;
    write_hit = wh;
  }

	// Destructor 
	~Cache();

	// define functions below
	void toString();

};

#endif // CACHE_H


