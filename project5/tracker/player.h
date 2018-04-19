#ifndef PLAYER__H
#define PLAYER__H

#include <list>
#include <cmath>
#include <ctime>
#include "sprite.h"
#include "projectile.h"

class SmartSprite;
class DumbSprite;

class Player : public Sprite {
public:
  Player(const std::string&);
  Player(const Player&);
  Player& operator= (const Player&);
  virtual ~Player() { }

  virtual void draw() const;
  virtual void update (Uint32 ticks);
  virtual void explode();

  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();
  void stop();

  void attach(SmartSprite* o);
  void detach(SmartSprite* o);

  void collided() { collision = true; }
  void missed()   { collision = false; }

  void shoot();

private:
  std::list<SmartSprite*> observers;
  bool collision;
  Vector2f startingVelocity;
  float slowDownFactor;
  DumbSprite* explosion;
  clock_t explosionStartTime;
  std::string projectileName;
  std::list<Projectile> projectiles;
  float minSpeed;
  float projectileInterval;
};
#endif
