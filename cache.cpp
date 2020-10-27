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
  bool evict = true; // will stay true if set is full
  // load + hit = 1 cycle
  // load + miss = 100 cycles + write data to cache
  // store + hit = 1 cycle and store hit
  // (write-through) store + miss = put data in cache
  if (l_s == 'l' && hit) {
    // ++cycleCount
    // ++loadHits
  } else if (l_s == 'l' && !hit) {
    // ++loadMisses
    // cycleCount += 100
    for(int i = 0; i < this->blocks_per_set; i++) { // iterate thru all blocks in set
      if (cache[index].set[i].getValid() == 0) { // if empty
	cache[index].set[i].setTag(tag); // set new tag
	cache[index].set[i].setValid(1); // set to full
	cache[index].set[i].setOrder(1); // make newest
	evict = false; // we don't have to evict anything
        // update orders for everything else in set
	for(int i = 0; i < this->blocks_per_set; i++) {
          if (cache[index].set[i].getTag() != tag && cache[index].set[i].getValid() == 1) {
            cache[index].set[i].setOrder(cache[index].set[i].getOrder() + 1);
          }
        }
	break;
      }
    }
    if (evict) { // this is LRU
      for(int i = 0; i < this->blocks_per_set; i++) {
        cout << this->blocks_per_set << endl;
	if (cache[index].set[i].getOrder() == this->blocks_per_set) {
	  cache[index].set[i].setTag(tag);
	  cache[index].set[i].setValid(1);
	  cache[index].set[i].setOrder(1);
	}
      }
    }
  } else if (l_s == 's' && hit) {
    // ++storeHits
    // ++cycleCount
  } else if (l_s == 's' && !hit) {
    // ++storeMisses
    // cycleCount += 100
    // currently write-through
    for(int i = 0; i < this->blocks_per_set; i++) {
      if (cache[index].set[i].getValid() == 0) {
	cache[index].set[i].setTag(tag); 
	cache[index].set[i].setValid(1);
	cache[index].set[i].setOrder(1);
	evict = false;
	break;
      }
    }
    if (evict) {
      for(int i = 0; i < this->blocks_per_set; i++) {
        if (cache[index].set[i].getOrder() == this->blocks_per_set) {
	  cache[index].set[i].setTag(tag); // I give up on this
	  cache[index].set[i].setValid(1);
	  cache[index].set[i].setOrder(1);
	}
      }
    }
  }
}

unsigned Cache::addressToUnsigned(string address) {
  return (unsigned) stoul(address, 0, 16);
}

unsigned Cache::extractIndex(unsigned address) {
  cout << "ind bits: " << this->num_index_bits << endl;
  cout << "off bits: " << this->num_offset_bits << endl;
  address = address << this->num_tag_bits;
  if (this->num_index_bits == 0) {
    return 0;
  } else {
    return address >> (32 - this->num_index_bits);
  }
}

unsigned Cache::extractTag(unsigned address) {
  return address >> (this->num_index_bits + this->num_offset_bits);
}

bool Cache::Hit(unsigned index, unsigned tag) {
  bool hit = false;
  Set s = this->cache[index];
  for(Block b : s.set) {
//    if(b.getTag() == tag && b.getValid() == 1) {
    if(b.getTag() == tag) {
      hit = true;
      return hit;
    }
  }

  return hit;
} 


