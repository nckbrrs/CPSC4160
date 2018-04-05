#ifndef SMARTMULTISPRITE__H
#define SMARTMULTISPRITE__H

#include <string>
#include "multiSprite.h"
#include "smartDrawable.h"

class Player;

class SmartMultiSprite : public MultiSprite, public SmartDrawable {
public:
  SmartMultiSprite(const std::string&, Player*);
  SmartMultiSprite(const SmartMultiSprite&);
  virtual ~SmartMultiSprite() { }

  virtual void update(Uint32 ticks);
  virtual void moveLeft();
  virtual void moveRight();
  virtual void moveUp();
  virtual void moveDown();

private:
  SmartMultiSprite& operator=(const SmartMultiSprite&);
};
#endif
