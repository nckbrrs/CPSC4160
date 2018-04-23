#ifndef DUMBSPRITE__H
#define DUMBSPRITE__H
#include <string>
#include "sprite.h"

class DumbSprite : public Sprite {
public:
  DumbSprite(const std::string& name) : Sprite(name) { }
  DumbSprite(const DumbSprite& s) : Sprite(s) { }
  virtual ~DumbSprite() { }
  virtual void update(Uint32 ticks);
  virtual void collided();
  void randomizeVelocity();
  void randomizePosition();
};
#endif
