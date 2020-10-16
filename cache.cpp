#include "cache.h"
#include <iostream>

using std::cout;
using std::endl;
void Cache::toString() {
  cout << "Number of sets: " << this->num_sets << endl;
  cout << "Write hit: " << this->write_hit << endl;
  cout << "Write miss: " << this->write_miss << endl;
}

Cache::~Cache() {

}

