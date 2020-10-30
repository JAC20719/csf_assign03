#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

using std::vector;
class Block {
 private:
  unsigned dirty;
 public:
  vector<unsigned> block{0, 0, 0};
  Block() {
    //All blocks invalid upon creation
    dirty = 0;
  } 

  void toString();

  unsigned getTag();

  unsigned getValid();

  unsigned getOrder();

  unsigned getDirty();
	
  void setTag(unsigned t);

  void setValid(unsigned v);

  void setOrder(unsigned o);

  void setDirty(unsigned d);
};

#endif // BLOCK_H
