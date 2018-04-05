#include <cmath>
#include <random>
#include <functional>
#include "smartMultiSprite.h"
#include "player.h"
#include "gameData.h"
#include "renderContext.h"

SmartMultiSprite::SmartMultiSprite(const std::string&name, Player* player) :
  MultiSprite(name),
  SmartDrawable(name, player)
{ }

SmartMultiSprite::SmartMultiSprite(const SmartMultiSprite& s) :
  MultiSprite(s),
  SmartDrawable(s)
{ }

void SmartMultiSprite::update(Uint32 ticks) {
  MultiSprite::update(ticks);
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

void SmartMultiSprite::moveLeft()  { setVelocityX( -abs(getVelocityX()) );  }
void SmartMultiSprite::moveRight() { setVelocityX( fabs(getVelocityX()) );  }
void SmartMultiSprite::moveUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void SmartMultiSprite::moveDown()  { setVelocityY( fabs(getVelocityY()) );  }
