#ifndef DUMBSPRITE__H
#define DUMBSPRITE__H
#include <string>
#include "sprite.h"

class DumbSprite : public Sprite {
public:
  DumbSprite(const std::string&);
  DumbSprite(const DumbSprite&);
  virtual ~DumbSprite() { }
  virtual void update(Uint32 ticks);
  virtual void explode();
};
#endif
