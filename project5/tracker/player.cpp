#include <ctime>
#include "gameData.h"
#include "player.h"
#include "smartSprite.h"
#include "dumbSprite.h"

Player::Player(const std::string& name) :
  Sprite(name),
  observers(),
  collision(false),
  startingVelocity(getVelocity()),
  slowDownFactor(GameData::getInstance().getXmlFloat(name+"/slowDownFactor")),
  explosion(nullptr),
  explosionStartTime(-1),
  projectileName(GameData::getInstance().getXmlStr(name+"/projectileName")),
  projectiles(),
  minSpeed(GameData::getInstance().getXmlInt(projectileName+"/minSpeed")),
  projectileInterval(GameData::getInstance().getXmlInt(projectileName+"/interval"))
{ setVelocityX(0); setVelocityY(0); }

Player::Player(const Player& s) :
  Sprite(s),
  observers(s.observers),
  collision(s.collision),
  startingVelocity(s.getVelocity()),
  slowDownFactor(s.slowDownFactor),
  explosion(s.explosion),
  explosionStartTime(s.explosionStartTime),
  projectileName(s.projectileName),
  projectiles(s.projectiles),
  minSpeed(s.minSpeed),
  projectileInterval(s.projectileInterval)
{ setVelocityX(0); setVelocityY(0); }

Player& Player::operator= (const Player& s) {
  Sprite::operator=(s);
  observers = s.observers;
  collision = s.collision;
  startingVelocity = s.startingVelocity;
  slowDownFactor = s.slowDownFactor;
  explosion = s.explosion;
  projectileName = s.projectileName;
  projectiles = s.projectiles;
  minSpeed = s.minSpeed;
  projectileInterval = s.projectileInterval;
  return *this;
}

void Player::stop() {
  setVelocityX(slowDownFactor * getVelocityX());
  setVelocityY(slowDownFactor * getVelocityY());
}

void Player::moveRight() {
  if (!isExploding()) {
    if (getPositionX() < getMaxPosBoundaryX() - getScaledWidth()) {
      setVelocityX(startingVelocity[0]);
    }
  }
}

void Player::moveLeft() {
  if (!isExploding()) {
    if (getPositionX() > getMinPosBoundaryX()) {
      setVelocityX(-startingVelocity[0]);
    }
  }
}

void Player::moveUp() {
  if (!isExploding()) {
    if (getPositionY() > getMinPosBoundaryY()) {
      setVelocityY(-startingVelocity[1]);
    }
  }
}

void Player::moveDown() {
  if (!isExploding()) {
    if (getPositionY() < getMaxPosBoundaryY() - getScaledHeight()) {
      setVelocityY(startingVelocity[1]);
    }
  }
}

void Player::draw() const {
  if (isExploding()) explosion->draw();
  else getImage()->draw(getPositionX(), getPositionY(), getScale());

  for (const Projectile& projectile : projectiles) {
    projectile.draw();
  }
}

void Player::update(Uint32 ticks) {
  if (isExploding()) {
    explosion->update(ticks);
    projectiles.clear();
    if (((clock() - explosionStartTime) / (double)CLOCKS_PER_SEC) > 0.1) {
      setExploding(false);
      delete explosion;
      explosion = NULL;
    }
    return;
  }

  if (!collision) {
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
  } else {
    std::cout << "COLLIDED!" << std::endl;
  }

  auto it = projectiles.begin();
  while (it != projectiles.end()) {
    (*it).update(ticks);
    if ((*it).isTooFar()) {
      it = projectiles.erase(it);
    }
    it++;
  }

  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while (ptr != observers.end()) {
    (*ptr)->setPlayerPos(getPosition());
    ++ptr;
  }

  stop();
}

void Player::explode() {
  setExploding(true);
  explosion = new DumbSprite("Explosion");
  explosion->setPosition(getPosition());
  explosion->setVelocityX(0);
  explosion->setVelocityY(0);
  explosionStartTime = clock();
}


void Player::attach(SmartSprite* o) {
  observers.push_back(o);
}

void Player::detach(SmartSprite* o) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while (ptr != observers.end()) {
    if (*ptr == o) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void Player::shoot() {
  if (!isExploding()) {
    if (getTimeSinceLastFrame() < projectileInterval) return;
    float dx = getScaledWidth();
    float dy = getScaledHeight()/2;
    Projectile projectile(projectileName);
    projectiles.push_back(projectile);
    if (getVelocityX() >= 0) {
      projectiles.back().setPosition(getPosition() + Vector2f(3*dx/4, dy));
      projectiles.back().setStartingPos(projectiles.back().getPosition());
      projectiles.back().setVelocity(getVelocity() + Vector2f(minSpeed, 0));
    } else {
      projectiles.back().setPosition(getPosition() + Vector2f(-dx/4, dy));
      projectiles.back().setStartingPos(projectiles.back().getPosition());
      projectiles.back().setVelocity(getVelocity() + Vector2f(-minSpeed, 0));
    }
  }
}
