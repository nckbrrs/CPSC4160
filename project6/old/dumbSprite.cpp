#include <cmath>
#include <random>
#include <functional>
#include "dumbSprite.h"
#include "gameData.h"
#include "renderContext.h"

void DumbSprite::randomizeVelocity() {
  float vx = getVelocityX();
  float vy = getVelocityY();
  float newvx = GameData::getInstance().getRandFloat(vx-50, vx+50);
  float newvy = GameData::getInstance().getRandFloat(vy-50, vy+50);
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
  setVelocity(Vector2f(newvx, newvy));
}

void DumbSprite::randomizePosition() {
  float px = getPositionX();
  float py = getPositionY();
  float newpx = GameData::getInstance().getRandFloat(px-50, px+50);
  float newpy = GameData::getInstance().getRandFloat(py-50, py+50);
  newpx *= [](){ if(rand()%2) return -1; else return 1; }();
  newpy *= [](){ if(rand()%2) return -1; else return 1; }();
  setPosition(Vector2f(newpx, newpy));
}

void DumbSprite::update(Uint32 ticks) {
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
}

void DumbSprite::collide() {
  std::cout << "dumbSprite " << getName() << " collided" << std::endl;
}
