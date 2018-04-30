#ifndef FALLINGSPRITE__H
#define FALLINGSPRITE__H
#include <string>
#include "sprite.h"

class FallingSprite : public Sprite {
public:
  FallingSprite(const std::string& name) : Sprite(name) { }
  FallingSprite(const FallingSprite& s) : Sprite(s) { }
  virtual ~FallingSprite() { }
  virtual void update(Uint32 ticks);
  virtual void collided();
  void randomizeVelocity();
  void randomizePosition();
};
#endif
