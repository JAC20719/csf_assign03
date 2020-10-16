#include "set.h"
#include <iostream>

using std::cout;
using std::endl;
Set::~Set() {
  
}

long unsigned Set::getIndex() {
  return this->index;
}

void Set::toString() {
  cout << "     --Set--" << endl;
  cout << "     Index:" << this->index << endl;
  for (int i = 0; i < this->blocks_per_set; i++) {
    this->set[i].toString();
  }
}
