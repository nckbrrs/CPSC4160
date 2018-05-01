#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H

#include <string>
#include "sprite.h"

class Player;
class DumbSprite;

class SmartSprite : public Sprite {
public:
  SmartSprite(const std::string&, const Player*);
  SmartSprite(const SmartSprite&);
  virtual ~SmartSprite() { }

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual void collide();

  enum Mode {Normal, Evade};

  const Vector2f& getPlayerPos() const { return playerPos; }
  int getPlayerWidth() const           { return playerWidth; }
  int getPlayerHeight() const          { return playerHeight; }
  float getSafeDistance() const        { return safeDistance; }
  Mode getCurrentMode() const          { return currentMode; }
  bool hasCollided() const             { return collided; }
  bool isColliding() const             { return colliding; }

  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  void setPlayerWidth(int w)           { playerWidth = w; }
  void setPlayerHeight(int h)          { playerHeight = h; }
  void setSafeDistance(float sd)       { safeDistance = sd; }
  void setCurrentMode(Mode m)          { currentMode = m; }
  void randomizeVelocity();
  void randomizePosition();

private:
  Mode currentMode;
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  float safeDistance;
  bool collided;
  bool colliding;
  DumbSprite* explosion;
  unsigned int explosionStartTime;

  void moveLeft()  { setVelocityX(-abs(getVelocityX()));  }
  void moveRight() { setVelocityX(fabs(getVelocityX()));  }
  void moveUp()    { setVelocityY(-fabs(getVelocityY())); }
  void moveDown()  { setVelocityY(fabs(getVelocityY()));  }
};
#endif
