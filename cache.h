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
 public:
  vector<Set> cache;
  
	// constructor
  Cache(int n, string wm, string wh) {
    cache.push_back(n);
    write_miss = wm;
    write_hit = wh;
  }

	// Destructor 
	~Cache();

	// define functions below
	void toString();

};

#endif // CACHE_H


