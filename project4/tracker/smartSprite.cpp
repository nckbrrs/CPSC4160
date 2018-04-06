#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "gameData.h"
#include "player.h"

SmartSprite::SmartSprite(const std::string& name, const Player* p) :
  Sprite(name),
  currentMode(Normal),
  playerPos(p->getPosition()),
  playerWidth(p->getScaledWidth()),
  playerHeight(p->getScaledHeight()),
  safeDistance(GameData::getInstance().getXmlFloat(name+"/safeDistance"))
{
  float vx = getVelocityX();
  float vy = getVelocityY();
  float newvx = GameData::getInstance().getRandFloat(vx-50, vx+50);
  float newvy = GameData::getInstance().getRandFloat(vy-50, vy+50);
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
  setVelocity(Vector2f(newvx, newvy));
}

SmartSprite::SmartSprite(const SmartSprite& s) :
  Sprite(s),
  currentMode(s.currentMode),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  safeDistance(s.safeDistance)
{ }

void SmartSprite::update(Uint32 ticks) {
  setTimeSinceLastFrame(getTimeSinceLastFrame() + ticks);
  if (getTimeSinceLastFrame() > getFrameInterval()) {
    if (isTwoWay()) {
      if (getVelocityX() >= 0) {
        setCurrentFrame(((getCurrentFrame()+1) % (getNumFrames()/2)));
      } else {
        setCurrentFrame((getNumFrames()/2) + ((getCurrentFrame()+1) % (getNumFrames()/2)));
      }
    } else {
      setCurrentFrame((getCurrentFrame()+1) % getNumFrames());
    }
    setTimeSinceLastFrame(0);
  }

  setPosition(getPosition() + (getVelocity() * static_cast<float>(ticks) * 0.001));

  if (getPositionY() < getMinPosBoundaryY()) {
    setVelocityY(std::abs(getVelocityY()));
  }
  if (getPositionY() > getMaxPosBoundaryY() - getScaledHeight()) {
    setVelocityY(-std::abs(getVelocityY()));
  }
  if ( getPositionX() < getMinPosBoundaryX()) {
    setVelocityX(std::abs(getVelocityX()));
  }
  if ( getPositionX() > getMaxPosBoundaryX() - getScaledWidth()) {
    setVelocityX(-std::abs(getVelocityX()));
  }

  float x = getPositionX() + getImage()->getWidth()/2;
  float y = getPositionY() + getImage()->getHeight()/2;
  float ex = getPlayerPos()[0] + getPlayerWidth()/2;
  float ey = getPlayerPos()[1] + getPlayerHeight()/2;
  float distanceToEnemy = hypot((x-ex), (y-ey));

  if (getCurrentMode() == Normal) {
    if (distanceToEnemy < getSafeDistance()) {
      setCurrentMode(Evade);
    }
  } else if (getCurrentMode() == Evade) {
    if (distanceToEnemy > getSafeDistance()) {
      setCurrentMode(Normal);
    } else {
      if (x < ex) moveLeft();
      if (x > ex) moveRight();
      if (y < ey) moveUp();
      if (y > ey) moveDown();
    }
  }
}
