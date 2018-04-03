#ifndef PLAYER__H
#define PLAYER__H

#include "twoWayMultiSprite.h"

class Player : public TwoWayMultiSprite {
public:
  Player(const std::string&);
  Player(const Player&);
  Player& operator= (const Player&);

  virtual void update (Uint32 ticks);

  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();
  void stop();

  void collided() { collision = true; }
  void missed()   { collision = false; }

private:
  bool collision;
  float slowDownFactor;
  Vector2f startingVelocity;
};
#endif
