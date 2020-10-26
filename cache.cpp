#include "cache.h"
#include <iostream>

using std::cout;
using std::endl;
void Cache::toString() {
  cout << "--Cache--" << endl;
  cout << "Number of sets: " << this->num_sets << endl;
  cout << "Write hit: " << this->write_hit << endl;
  cout << "Write miss: " << this->write_miss << endl;

  for(int i = 0; i < this->num_sets; i++) {
    this->cache[i].toString();
  }
}

Cache::~Cache() {

}

void Cache::cpuRequest(char l_s, string address) {
  cout << endl;
  cout << "--CACHE REQUEST--" << endl;
  cout << "address: " << address << endl;
  cout << "load or store: " << l_s << endl;
  unsigned u_address = addressToUnsigned(address);
   cout << "int address: " << u_address << endl;
  unsigned index = extractIndex(u_address);
  cout << "index: " << index << endl;
  unsigned tag = extractTag(u_address);
  cout << "tag: " << tag << endl;
  bool hit = Hit(index, tag);
  cout << "hit: " << hit << endl;

  //Handle write(based on miss hit rules)/load
}

unsigned Cache::addressToUnsigned(string address) {
  return (unsigned) stoul(address, 0, 16);
}

unsigned Cache::extractIndex(unsigned address) {
  cout << "ind bits: " << this->num_index_bits << endl;
  cout << "off bits: " << this->num_offset_bits << endl;
  address = address << (32 - (this->num_index_bits + this->num_offset_bits));
    return address >> (32 - this->num_offset_bits);
}

unsigned Cache::extractTag(unsigned address) {
  return address >> (this->num_index_bits + this->num_offset_bits);
}

bool Cache::Hit(unsigned index, unsigned tag) {
  bool hit = false;
  Set s = this->cache[index];
  for(Block b : s.set) {
    if(b.getTag() == tag && b.getValid() == 1) {
      hit = true;
    }
  }

  return hit;
} 

