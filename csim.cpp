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
  long unsigned num_sets = ( (long unsigned) (atol(argv[1])));
  long unsigned blocks_per_set = ( (long unsigned) (atol(argv[2])));
  long unsigned bytes_per_block = ((long unsigned) (atol(argv[3])));

  string write_miss = argv[4];
  string write_hit = argv[5];
  string timestamp = argv[6];
								  
  long unsigned num_offset_bits = log2(bytes_per_block * 8);
  long unsigned  num_index_bits = log2(num_sets);

  Cache cache = Cache(num_sets, write_miss, write_hit);
  cache.toString();

  
	char ls = '\0'; // store instruction
	string address; // store address
	string line; // get whole lines from file
	
	// start main loop, reading 1 instruction at a time
	while (getline(cin,line)) {
		ls = line[0];
		address = line.substr(2,10);
		cout << ls << " " << address << endl;
	}
	return 0;
}
