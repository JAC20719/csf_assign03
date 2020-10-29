#include "cache.h"
#include <iostream>

using std::cout;
using std::endl;
void Cache::toString() {
  //cout << "--Cache--" << endl;
  //cout << "Number of sets: " << this->num_sets << endl;
  //cout << "Write hit: " << this->write_hit << endl;
 // cout << "Write miss: " << this->write_miss << endl;

  for(int i = 0; i < this->num_sets; i++) {
    this->cache[i].toString();
    }
}

Cache::~Cache() {

}

void Cache::cpuRequest(char l_s, string address) {
  /*
  cout << endl;
  cout << "--CACHE REQUEST--" << endl;
  cout << "address: " << address << endl;
  cout << "load or store: " << l_s << endl;
  */
  unsigned u_address = addressToUnsigned(address);
  //cout << "int address: " << u_address << endl;
  unsigned index = extractIndex(u_address);
  //cout << "index: " << index << endl;
  unsigned tag = extractTag(u_address);
  //cout << "tag: " << tag << endl;
  bool hit = Hit(index, tag);
  //cout << "hit: " << hit << endl;
  if (l_s == 'l' && hit) {
    this->loadHits++; //Increase load hits
    load_hit(index, tag);
  } else if (l_s == 'l' && !hit) {
    this->loadMisses++; //Increase load misses
    load_miss(index, tag);
  } else if (l_s == 's' && hit) {
    this->storeHits++; //Increase store hits
    store_hit(index, tag);
  } else if (l_s == 's' && !hit) {
    this->storeMisses++; //Increase store misses
    store_miss(index, tag);
  }
}
unsigned Cache::addressToUnsigned(string address) {
  return (unsigned) stoul(address, 0, 16);
}

unsigned Cache::extractIndex(unsigned address) {
  //cout << "ind bits: " << this->num_index_bits << endl;
  //cout << "off bits: " << this->num_offset_bits << endl;
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
    if(b.getTag() == tag && b.getValid() == 1) {
//    if(b.getTag() == tag) {
      hit = true;
      return hit;
    }
  }

  return hit;
}

void Cache::store_miss(unsigned index, unsigned tag) {
  if(this->write_miss.compare("write-allocate") == 0) {
    
    write_allocate(index, tag); //Bring main mem into cache
  } else { //it was no-write-allocate
    
    no_write_allocate(index, tag); //Bring main mem straight to cpu, skip cache
  }
}

void Cache::store_hit(unsigned index, unsigned tag) {
  if(this->write_hit.compare("write-through") == 0) {
    
    write_through(index, tag); //Write to cache and main mem
  } else { //it was write-back
    
    write_back(index, tag); //Write to cache only, mark as block as dirty
  }
}

/* If a load hit, increase the cycle count by 1.
** If LRU, update orders.
*/
void Cache::load_hit(unsigned index, unsigned tag) {
  //Expense is load from cache of 1 cycle
  this->cycleCount++;
  if (this->timestamp.compare("lru") == 0) {
    for (int i = 0; i < this->blocks_per_set; i++) {
      if (cache[index].set[i].getTag() == tag) {
        cache[index].set[i].setOrder(1);
	updateOrder(index,tag);
      }
    }
  }
}

/* If load miss, write missed data to the cache from main memory.
** Both LRU and FIFO require that orders be updated.
*/
void Cache::load_miss(unsigned index, unsigned tag) {
  bool evict = true;
  for(int i = 0; i < this->blocks_per_set; i++) { // iterate thru all blocks in set
    if (cache[index].set[i].getValid() == 0) { // if empty
      cache[index].set[i].setTag(tag); // set new tag
      cache[index].set[i].setValid(1); // set to full
      cache[index].set[i].setOrder(1); // make newest
      evict = false; // we don't have to evict anything
      // update orders for everything else in set
      updateOrder(index, tag);
      /*
      for(int i = 0; i < this->blocks_per_set; i++) {
	if (cache[index].set[i].getTag() != tag && cache[index].set[i].getValid() == 1) {
	  cache[index].set[i].setOrder(cache[index].set[i].getOrder() + 1);
	}
      }
      */
      break;
    }
  }
  if (evict) { // if set is full
    int evicted_index = evict_block(index, tag);
    
    // This works because nothing is marked as dirty if write-through is param
    if(cache[index].set[evicted_index].getDirty() == 1) {
      //Set dirty bit to 0, now consistent with main mem
      cache[index].set[evicted_index].setDirty(0);
      //Extra expense of writing cache back to main mem
      //100 * (bytes_per_block / 4) cycles
      this->cycleCount += 100 * (this->bytes_per_block / 4);
    }
  }
  //Expense is loading from main mem to cache plus loading from cache
  //100 * (bytes_per_block / 4) cycles plus
  //1 cycle
  this->cycleCount += 100 * (this->bytes_per_block / 4);
  this->cycleCount++;
}

/* Update the orders of the blocks in a set by increasing the 
** order field by 1
*/
void Cache::updateOrder(unsigned index, unsigned tag) {
  for(int i = 0; i < this->blocks_per_set; i++) {
    if (cache[index].set[i].getTag() != tag && cache[index].set[i].getValid() == 1) {
       cache[index].set[i].setOrder(cache[index].set[i].getOrder() + 1);
    }
  }
}


void Cache::write_through(unsigned index, unsigned tag) {
  for(int i = 0; i < this->blocks_per_set; i++) { // iterate thru all blocks in set
    if (cache[index].set[i].getTag() == tag) { // if correct block
      cache[index].set[i].setOrder(1); // make newest
      // update orders for everything else in set
      // this happens for both LRU and FIFO
      updateOrder(index, tag);
      /*
      for(int i = 0; i < this->blocks_per_set; i++) {
	if (cache[index].set[i].getTag() != tag && cache[index].set[i].getValid() == 1) {
	  cache[index].set[i].setOrder(cache[index].set[i].getOrder() + 1);
	}
      }
      */
      break;
    }
  }
  //Expense is writing to cache and main mem
  //1 cycle plus
  //100 * (bytes_per_block / 4) cycles
  this->cycleCount += 100 * (this->bytes_per_block / 4);
  this->cycleCount++;
}

void Cache::write_back(unsigned index, unsigned tag) {
  for(int i = 0; i < this->blocks_per_set; i++) { // iterate thru all blocks in set
    if (cache[index].set[i].getTag() == tag) { // if block in question
      cache[index].set[i].setDirty(1); // mark dirty bit
      cache[index].set[i].setOrder(1); // make newest
      // update orders for everything else in set
      updateOrder(index, tag);
      /*
      for(int i = 0; i < this->blocks_per_set; i++) {
	if (cache[index].set[i].getTag() != tag && cache[index].set[i].getValid() == 1) {
	  cache[index].set[i].setOrder(cache[index].set[i].getOrder() + 1);
	}
      }
      */
      break;
    }
  }
  //Write back has expense of 1, writing to cache only
  //1 cycle
  this->cycleCount++;
}

void Cache::write_allocate(unsigned index, unsigned tag) {
  bool evict = true;
  for(int i = 0; i < this->blocks_per_set; i++) { // iterate thru all blocks in set
    if (cache[index].set[i].getValid() == 0) { // if empty
      cache[index].set[i].setTag(tag); // set new tag
      cache[index].set[i].setValid(1); // set to full
      cache[index].set[i].setOrder(1); // make newest
      evict = false; // we don't have to evict anything
      // update orders for everything else in set
      // This happens for both FIFO and LRU
      updateOrder(index, tag);
      /*
      for(int i = 0; i < this->blocks_per_set; i++) {
	if (cache[index].set[i].getTag() != tag && cache[index].set[i].getValid() == 1) {
	  cache[index].set[i].setOrder(cache[index].set[i].getOrder() + 1);
	}
      }
      */
      break;
    }
  }
  if (evict) {
    int evicted_index = evict_block(index, tag);
    if(cache[index].set[evicted_index].getDirty() == 1) {
      //Extra expense of writing cache back to main mem (dirty bit indicated write back is being used)
      //100 * (bytes_per_block / 4) cycles
      this->cycleCount += 100 * (this->bytes_per_block / 4);
    }
  }
  //Write allocate cost is loading from main mem to cache plus writing to cache
  //100 * (bytes_per_block / 4) cycles plus
  //1 cycle
  this->cycleCount += 100 * (this->bytes_per_block / 4);
  this->cycleCount++;
}

void Cache::no_write_allocate(unsigned index, unsigned tag) {
  //No write allocate has cost of writing straight to main mem
  //100 * (bytes_per_block / 4)
  this->cycleCount += 100 * (this->bytes_per_block / 4);
}

/* Given index of a set to search and tag of a block that will replace
** old block, find the block that should be replaced and return it's position
** within the set 
*/
int Cache::evict_block(unsigned index, unsigned tag) {
 // if(this->timestamp.compare("lru") == 0) { //lru
    for(int i = 0; i < this->blocks_per_set; i++) {
    //  cout << this->blocks_per_set << endl;
      if (cache[index].set[i].getOrder() == this->blocks_per_set) {
	cache[index].set[i].setTag(tag);
	cache[index].set[i].setValid(1);
	cache[index].set[i].setOrder(1);
	return i;
      }
    }
  return -1;
}

/* Return the current cycle count */
int Cache::getCycleCount() {
  return this->cycleCount;
}

/* Return current load misses */
int Cache::getLoadMisses() {
  return this->loadMisses;
}

/* Return current load hits */
int Cache::getLoadHits() {
  return this->loadHits;
}

/* return current store misses */
int Cache::getStoreMisses() {
  return this->storeMisses;
}

/* Return current store hits */
int Cache::getStoreHits() {
  return this->storeHits;
}


