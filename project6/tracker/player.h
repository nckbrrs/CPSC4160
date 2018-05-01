#ifndef PLAYER__H
#define PLAYER__H

#include <list>
#include <cmath>
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

  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();
  void stop();
  void attach(SmartSprite* o);
  void detach(SmartSprite* o);
  void collide();
  void shoot();

  std::list<Projectile*> getActiveProjectiles() const { return activeProjectiles; }
  std::list<Projectile*> getFreeProjectiles() const { return freeProjectiles; }
  unsigned int getLivesLeft() const { return livesLeft; }

private:
  bool facingRight;
  std::list<SmartSprite*> observers;
  bool collision;
  Vector2f startingVelocity;
  float slowDownFactor;
  DumbSprite* explosion;
  unsigned int explosionStartTime;
  std::string projectileName;
  std::list<Projectile*> activeProjectiles;
  std::list<Projectile*> freeProjectiles;
  unsigned int livesLeft;

  float minSpeed;
  float projectileInterval;
  float timeSinceLastShot;
};
#endif
