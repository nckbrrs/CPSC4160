#ifndef PLAYER__H
#define PLAYER__H

#include "twoWayMultiSprite.h"

class Player : public TwoWayMultiSprite {
public:
  Player(const std::string&);
  Player(const Player&);
  Player& operator= (const Player&);

  virtual void update (Uint32 ticks);

  void right();
  void left();
  void up();
  void down();
  void stop();

  void collided() { collision = true; }
  void missed()   { collision = false; }

private:
  bool collision;
  float slowDownFactor;
  Vector2f startingVelocity;
};
#endif
