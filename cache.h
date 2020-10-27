#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <vector>
#include "set.h"

using std::string;
using std::vector;
class Cache {
 private:
  //Bringing in all info to cache, thought was we will do bulk of work here?
  string write_miss = "";
  string write_hit = "";
  int num_sets;
  int num_index_bits;
  int num_offset_bits;
  int num_tag_bits;
  int blocks_per_set;
  string timestamp;
  int num_loads; //track number of loads from cache
  int num_stores; //track number of stores to cache
 public:
  vector<Set> cache;
  
	// constructor
  Cache(int ns, string wm, string wh, int nib,
	int nob, int ntb, int bps, string t) {
    num_sets = ns;
    write_miss = wm;
    write_hit = wh;
    num_index_bits = nib;
    num_offset_bits = nob;
    num_tag_bits = ntb;
    blocks_per_set = bps;
    timestamp = t; 
    num_loads = 0;
    num_stores = 0;

     for(int i = 0; i < num_sets; i++) {
       cache.push_back(Set(blocks_per_set, i));
    }
  }

	// Destructor 
	~Cache();

	// define functions below
	void toString();

	void cpuRequest(char l_s, string address); //Call to cache from cpu for loads/stores

 private:
	unsigned extractIndex(unsigned address);  //Get index of address

	unsigned extractTag(unsigned address); //Get tag address

	bool Hit(unsigned index, unsigned tag); //Check if hit or miss

	unsigned addressToUnsigned(string address);

	

};

#endif // CACHE_H


