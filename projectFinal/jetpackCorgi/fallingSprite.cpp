#include <cmath>
#include <random>
#include <functional>
#include "fallingSprite.h"
#include "gameData.h"
#include "renderContext.h"
#include <time.h>

void FallingSprite::randomizeVelocity() {
  float vy = getVelocityY();
  float newvy = GameData::getInstance().getRandFloat(50, vy+50);
  setVelocity(Vector2f(0, newvy));
}

void FallingSprite::randomizePosition() {
  float newpx = GameData::getInstance().getRandFloat(-10, GameData::getInstance().getXmlInt("background/width") );
  float newpy = GameData::getInstance().getRandFloat(-10, GameData::getInstance().getXmlInt("background/height"));
  setPosition(Vector2f(newpx, newpy));
}

void FallingSprite::update(Uint32 ticks) {
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

  if (getPositionY() > getMaxPosBoundaryY()) {
    setPositionY(0 - getScaledHeight());
  }
}

void FallingSprite::collide() {
  std::cout << "fallingSprite " << getName() << "collided" << std::endl;
}
