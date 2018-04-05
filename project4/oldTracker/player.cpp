#include "gameData.h"
#include "player.h"
#include "smartDrawable.h"

Player::Player(const std::string& name) :
  MultiSprite(name),
  collision(false),
  slowDownFactor(GameData::getInstance().getXmlFloat(name+"/slowDownFactor")),
  startingVelocity(getVelocity()),
  observers()
{ setVelocityX(0); setVelocityY(0); }

Player::Player(const Player& s) :
  MultiSprite(s),
  collision(s.collision),
  slowDownFactor(s.slowDownFactor),
  startingVelocity(s.getVelocity()),
  observers(s.observers)
{ setVelocityX(0); setVelocityY(0); }

Player& Player::operator= (const Player& s) {
  MultiSprite::operator=(s);
  collision = s.collision;
  slowDownFactor = s.slowDownFactor;
  startingVelocity = s.startingVelocity;
  observers = s.observers;
  return *this;
}

void Player::stop() {
  setVelocityX(slowDownFactor * getVelocityX());
  setVelocityY(slowDownFactor * getVelocityY());
}

void Player::moveRight() {
  if (getPositionX() < getMaxPosBoundaryX() - getScaledWidth()) {
    setVelocityX(startingVelocity[0]);
  }
}

void Player::moveLeft() {
  if (getPositionX() > getMinPosBoundaryX()) {
    setVelocityX(-startingVelocity[0]);
  }
}

void Player::moveUp() {
  if (getPositionY() > getMinPosBoundaryY()) {
    setVelocityY(-startingVelocity[1]);
  }
}

void Player::moveDown() {
  if (getPositionY() < getMaxPosBoundaryY() - getScaledHeight()) {
    setVelocityY(startingVelocity[1]);
  }
}

void Player::update(Uint32 ticks) {
  if (!collision) MultiSprite::update(ticks);
  std::list<SmartDrawable*>::iterator ptr = observers.begin();
  while (ptr != observers.end() ) {
    (*ptr)->setPlayerPos(getPosition());
    ++ptr;
  }
  stop();
}

void Player::attach(SmartDrawable* o) {
  observers.push_back(o);
}

void Player::detach(SmartDrawable* o) {
  std::list<SmartDrawable*>::iterator ptr = observers.begin();
  while (ptr != observers.end()) {
    if (*ptr == o) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}
