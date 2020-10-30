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
string checkNumParameters(int sets, int blocks, int bytes) {
  if (!isPowerof2(sets)) { 
    return  "1st parameter invalid";
  } else if (!isPowerof2(blocks)) {
    return "2nd parameter invalid";
  } else if (!isPowerof2(bytes) || bytes < 4) {
    return "3rd parameter invalid";
  }
  return "\0";
}

/* check 4th parameter validity */
string check4thParam(string miss) {
  if (miss.compare("write-allocate") == 0 || miss.compare("no-write-allocate") == 0) {
    return "\0";
  } else {
    return "4th parameter invalid";
  }
}

/* check 5th param validity */
string check5thParam(string hit) { 
  if (hit.compare("write-through") == 0 || hit.compare("write-back") == 0) {
    return "\0";
  } else {
    return "5th parameter invalid";
  }
}

/* check 6th param validity */
string check6thParam(string replace) {
  if (replace.compare("lru") == 0 || replace.compare("fifo") == 0) {
    return "\0";
  } else {
    return "6th parameter invalid";
  }
}

/* Check that all string parameters are valid inputs */
string checkStringParameters(string miss, string hit, string replace) {
  string fourth = check4thParam(miss);
  string fifth = check5thParam(hit);
  string sixth = check6thParam(replace);
  if (!fourth.empty()) {
    return fourth;
  } else if (!fifth.empty()) {
    return fifth;
  } else if (!sixth.empty()) {
    return sixth;
  }
  return "\0";
}
  
  
int main(int argc, char** argv){
  // receive all command line args and check validity
  if (argc != 7) {
    cout << "incorrect number of parameters" << endl;
    return 1;
  }
  int num_sets = ((int) (atol(argv[1])));
  int blocks_per_set = ((int) (atol(argv[2])));
  int bytes_per_block = ((int) (atol(argv[3])));
  string error_message1 = checkNumParameters(num_sets, blocks_per_set, bytes_per_block);
  if (!error_message1.empty()) { 
    cout << error_message1 << endl;
    return 1;
  }
  string write_miss = argv[4];
  string write_hit = argv[5];
  string replacement = argv[6];
  string error_message = checkStringParameters(write_miss, write_hit, replacement);
  if (!error_message.empty()) {
    cout << error_message << endl;
    return 1;
  }
  // calculate the # bits for each part of the address 
  int cache_size = bytes_per_block * blocks_per_set * num_sets;
  int num_offset_bits = (int) log2(bytes_per_block);
  int num_index_bits = (int) log2(cache_size) - (int) log2(blocks_per_set) - num_offset_bits;
  int num_tag_bits = 32 - num_index_bits - num_offset_bits;
  // initialize the cache 
  Cache cache = Cache(num_sets, write_miss, write_hit, num_index_bits, num_offset_bits, num_tag_bits, blocks_per_set, bytes_per_block, replacement);
  //cache.toString();

  char ls = '\0'; // store instruction
  string address; // store address
  string line; // get whole lines from file
  int numLoads = 0;
  int numStores = 0;
  // start main loop, reading 1 instruction at a time
  while (getline(cin,line)) {
    ls = line[0];
    if (ls == 'l') {
      numLoads++;
    } else if (ls == 's') {
      numStores++;
    }
    address = line.substr(4,10);
    //cout << ls << " " << address << endl;
    cache.cpuRequest(ls, address);	
    //cache.toString();
  }
  
  cout << "Total loads: " << cache.getLoadMisses() + cache.getLoadHits() << endl;
  cout << "Total stores: " << numStores << endl;
  cout << "Load hits: " << cache.getLoadHits() << endl;
  cout << "Load misses: " << cache.getLoadMisses() << endl;
  cout << "Store hits: " << cache.getStoreHits() << endl;
  cout << "Store misses: " << cache.getStoreMisses() << endl;
  cout << "Total Cycles: " << cache.getCycleCount() << endl;

  return 0;
}
