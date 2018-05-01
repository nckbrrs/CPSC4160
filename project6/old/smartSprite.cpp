#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "dumbSprite.h"
#include "gameData.h"
#include "player.h"
#include "clock.h"
#include "sound.h"

SmartSprite::SmartSprite(const std::string& name, const Player* p) :
  Sprite(name),
  currentMode(Normal),
  playerPos(p->getPosition()),
  playerWidth(p->getScaledWidth()),
  playerHeight(p->getScaledHeight()),
  safeDistance(GameData::getInstance().getXmlFloat(name+"/safeDistance")),
  collided(false),
  colliding(false),
  explosion(nullptr),
  explosionStartTime(-1)
{ }

SmartSprite::SmartSprite(const SmartSprite& s) :
  Sprite(s),
  currentMode(s.currentMode),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  safeDistance(s.safeDistance),
  collided(s.collided),
  colliding(s.colliding),
  explosion(s.explosion),
  explosionStartTime(s.explosionStartTime)
{ }

void SmartSprite::randomizeVelocity() {
  float vx = getVelocityX();
  float vy = getVelocityY();
  float newvx = GameData::getInstance().getRandFloat(vx-50, vx+50);
  float newvy = GameData::getInstance().getRandFloat(vy-50, vy+50);
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
  setVelocity(Vector2f(newvx, newvy));
}

void SmartSprite::randomizePosition() {
  float px = getPositionX();
  float py = getPositionY();
  float newpx = GameData::getInstance().getRandFloat(px-200, px+200);
  float newpy = GameData::getInstance().getRandFloat(py-200, py+200);
  newpx *= [](){ if(rand()%2) return -1; else return 1; }();
  newpy *= [](){ if(rand()%2) return -1; else return 1; }();
  setPosition(Vector2f(newpx, newpy));
}

void SmartSprite::draw() const {
  if (colliding) explosion->draw();
  else getImage()->draw(getPositionX(), getPositionY(), getScale());
}

void SmartSprite::update(Uint32 ticks) {
  if (colliding) {
    explosion->update(ticks);
    if ((Clock::getInstance().getSeconds() - explosionStartTime) >= 2) {
      colliding = false;
      delete explosion;
      explosion = NULL;
    }
    return;
  } else {
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
}

void SmartSprite::collide() {
  SDL_Sound::getInstance()[0];
  collided = true;
  colliding = true;
  setVelocityX(0);
  setVelocityY(0);
  explosion = new DumbSprite("Explosion");
  explosion->setPosition(getPosition());
  explosion->setVelocityX(0);
  explosion->setVelocityY(0);
  setPosition(Vector2f(-100, -100));
  setVelocity(Vector2f(0, 0));
  explosionStartTime = Clock::getInstance().getSeconds();
}
