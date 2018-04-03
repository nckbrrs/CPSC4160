#include "gameData.h"
#include "player.h"

Player::Player(const std::string& name) :
  TwoWayMultiSprite(name),
  collision(false),
  slowDownFactor(GameData::getInstance().getXmlInt(name+"/slowDownFactor")),
  startingVelocity(getVelocity())
{ }

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
  setVelocityY(0);
}

void Player::right() {
  if (getPositionX() < getMaxPosBoundaryX() - getScaledWidth()) {
    setVelocityX(startingVelocity[0]);
  }
}

void Player::left() {
  if (getPositionX() > getMinPosBoundaryX()) {
    setVelocityX(-startingVelocity[0]);
  }
}

void Player::up() {
  if (getPositionY() > getMinPosBoundaryY()) {
    setVelocityY(-startingVelocity[1]);
  }
}

void Player::down() {
  if (getPositionY() < getMaxPosBoundaryY() - getScaledHeight()) {
    setVelocityY(startingVelocity[1]);
  }
}

void Player::update(Uint32 ticks) {
  if (!collision) TwoWayMultiSprite::update(ticks);
  stop();
}
