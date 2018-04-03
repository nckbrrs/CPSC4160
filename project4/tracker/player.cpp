#include "gameData.h"
#include "player.h"

Player::Player(const std::string& name) :
  TwoWayMultiSprite(name),
  collision(false),
  slowDownFactor(GameData::getInstance().getXmlFloat(name+"/slowDownFactor")),
  startingVelocity(getVelocity())
{ setVelocityX(0); setVelocityY(0); }

Player::Player(const Player& s) :
  TwoWayMultiSprite(s),
  collision(s.collision),
  slowDownFactor(s.slowDownFactor),
  startingVelocity(s.getVelocity())
{ }

Player& Player::operator= (const Player& s) {
  TwoWayMultiSprite::operator=(s);
  collision = s.collision;
  slowDownFactor = s.slowDownFactor;
  startingVelocity = s.startingVelocity;
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
  if (!collision) TwoWayMultiSprite::update(ticks);
  stop();
}
