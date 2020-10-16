#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include "cache.h"
using std::cin; using std::cout; using std::endl;
using std::string;
using std::getline;
int main(int argc, char** argv){
  int num_sets = ((int) (atol(argv[1])));
  int blocks_per_set = ((int) (atol(argv[2])));
  int bytes_per_block = ((int) (atol(argv[3])));

  string write_miss = argv[4];
  string write_hit = argv[5];
  string timestamp = argv[6];
								  
  int num_offset_bits = (int) log2(bytes_per_block * 8);
  int num_index_bits = (int) log2(num_sets);

  Cache cache = Cache(num_sets, write_miss, write_hit, num_index_bits, num_offset_bits, blocks_per_set, timestamp);
  cache.toString();

  
	char ls = '\0'; // store instruction
	string address; // store address
	string line; // get whole lines from file
	
	// start main loop, reading 1 instruction at a time
	while (getline(cin,line)) {
		ls = line[0];
		address = line.substr(4,10);
		cout << ls << " " << address << endl;
		cache.cpuRequest(ls, address);
	}
	return 0;
}
