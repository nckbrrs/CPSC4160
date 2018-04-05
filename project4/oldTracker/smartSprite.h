#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H

#include <string>
#include "sprite.h"
#include "smartDrawable.h"

class Player;

class SmartSprite : public Sprite, public SmartDrawable {
public:
  SmartSprite(const std::string&, Player*);
  SmartSprite(const SmartSprite&);
  virtual ~SmartSprite() { }

  virtual void update(Uint32 ticks);
  virtual void moveLeft();
  virtual void moveRight();
  virtual void moveUp();
  virtual void moveDown();

private:
  SmartSprite& operator=(const SmartSprite&);
};
#endif
