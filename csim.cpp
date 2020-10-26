#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include "cache.h"
using std::cin; using std::cout; using std::endl;
using std::string;
using std::getline;

/* Check if an integer is a power of 2 */
bool isPowerof2(int i) {
  if(i == 0) {
    return false;
  }
  return (ceil(log2(i)) == floor(log2(i)));
}

/* Check that all parameters are powers of 2 */
bool checkNumParameters(int sets, int blocks, int bytes) {
  return (isPowerof2(sets) && isPowerof2(blocks) && isPowerof2(bytes) && bytes >= 4);
}

/* Check that all string parameters are valid inputs */
bool checkStringParameters(string miss, string hit, string replace) {
  if (miss.compare("write-allocate") != 0) {
    return false;
  } else if (miss.compare("no-write-allocate") != 0) {
    return false;
  } else if (hit.compare("write-through") != 0) {
    return false;
  } else if (hit.compare("write-back") != 0) {
    return false;
  } else if (replace.compare("lru") != 0) {
    return false;
  } else if (replace.compare("fifo") != 0) {
    return false;
  }
}

int main(int argc, char** argv){
  int num_sets = ((int) (atol(argv[1])));
  int blocks_per_set = ((int) (atol(argv[2])));
  int bytes_per_block = ((int) (atol(argv[3])));
  if (!checkNumParameters(num_sets, blocks_per_set, bytes_per_block)) {
    cout << "invalid parameters 1" << endl;
    return 1;
  }
  string write_miss = argv[4];
  string write_hit = argv[5];
  string replacement = argv[6];
  if (checkStringParameters(write_miss, write_hit, replacement)) {
    cout << "invalid parameters 2" << endl;
    return 1;
  }
  int cache_size = bytes_per_block * blocks_per_set * num_sets;
  int num_offset_bits = (int) log2(bytes_per_block);
  int num_index_bits = (int) log2(cache_size) - (int) log2(blocks_per_set) - num_offset_bits;
  int num_tag_bits = 32 - num_index_bits - num_offset_bits;
  cout << cache_size << endl;
  cout << num_offset_bits << endl;
  cout << num_index_bits << endl;
  cout << num_tag_bits << endl;

  Cache cache = Cache(num_sets, write_miss, write_hit, num_index_bits, num_offset_bits, blocks_per_set, replacement);
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
