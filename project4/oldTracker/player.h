#ifndef PLAYER__H
#define PLAYER__H

#include <list>
#include "multiSprite.h"

class SmartDrawable;

class Player : public MultiSprite {
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

  void attach(SmartDrawable* o);
  void detach(SmartDrawable* o);

  void collided() { collision = true; }
  void missed()   { collision = false; }

private:
  bool collision;
  float slowDownFactor;
  Vector2f startingVelocity;
  std::list<SmartDrawable*> observers;
};
#endif