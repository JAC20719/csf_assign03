#include "block.h"
#include <iostream>

using std::cout;
using std::endl;
Block::~Block() {

}

void Block::toString() {
  cout << "          --Block--" << endl;
  cout << "          Tag: " << this->block[0] << endl;
  cout << "          Valid: " << this->block[1] << endl;
  cout << "          Order: " << this->block[2] << endl;
}

unsigned Block::getTag() {
  return this->block[0];
}

unsigned Block::getValid() {
  return this->block[1];
}

unsigned Block::getOrder() {
  return this->block[2];
}

void Block::setTag(unsigned t) {
  block[0] = t;
}

void Block::setValid(unsigned v) {
  block[1] = v;
}

void Block::setOrder(unsigned o) {
  block[2] = o;
}

