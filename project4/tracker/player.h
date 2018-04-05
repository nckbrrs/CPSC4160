#ifndef PLAYER__H
#define PLAYER__H

#include <list>
#include <cmath>
#include "sprite.h"

class SmartSprite;

class Player : public Sprite {
public:
  Player(const std::string&);
  Player(const Player&);
  Player& operator= (const Player&);
  virtual ~Player() { }

  virtual void update (Uint32 ticks);

  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();
  void stop();

  void attach(SmartSprite* o);
  void detach(SmartSprite* o);

  void collided() { collision = true; }
  void missed()   { collision = false; }

private:
  std::list<SmartSprite*> observers;
  bool collision;
  Vector2f startingVelocity;
  float slowDownFactor;
};
#endif
