#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "player.h"
#include "gameData.h"
#include "renderContext.h"

SmartSprite::SmartSprite(const std::string& name, Player* player) :
  Sprite(name),
  SmartDrawable(name, player)
{ }

SmartSprite::SmartSprite(const SmartSprite& s) :
  Sprite(s),
  SmartDrawable(s)
{ }

void SmartSprite::update(Uint32 ticks) {
  Sprite::update(ticks);
  float x = getPositionX() + getImage()->getWidth()/2;
  float y = getPositionY() + getImage()->getHeight()/2;
  float ex = getPlayerPos()[0] + getPlayerWidth()/2;
  float ey = getPlayerPos()[1] + getPlayerHeight()/2;
  float distanceToEnemy = hypot((x-ex), (y-ey));

  if (getCurrentMode() == NORMAL) {
    if (distanceToEnemy < getSafeDistance()) {
      setCurrentMode(EVADE);
    }
  } else if (getCurrentMode() == EVADE) {
    if (distanceToEnemy > getSafeDistance()) {
      setCurrentMode(NORMAL);
    } else {
      if (x < ex) moveLeft();
      if (x > ex) moveRight();
      if (y < ey) moveUp();
      if (y > ey) moveDown();
    }
  }
}

void SmartSprite::moveLeft()  { setVelocityX( -abs(getVelocityX()) );  }
void SmartSprite::moveRight() { setVelocityX( fabs(getVelocityX()) );  }
void SmartSprite::moveUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void SmartSprite::moveDown()  { setVelocityY( fabs(getVelocityY()) );  }
