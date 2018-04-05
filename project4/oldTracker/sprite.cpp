#include <cmath>
#include <random>
#include <functional>
#include "sprite.h"
#include "gameData.h"
#include "renderContext.h"

Vector2f Sprite::makeVelocity(int vx, int vy) const {
  float newvx = GameData::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = GameData::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();

  return Vector2f(newvx, newvy);
}

Sprite::Sprite(const std::string& name) :
  Drawable(name,
           Vector2f(GameData::getInstance().getXmlInt(name+"/startPos/x"),
                    GameData::getInstance().getXmlInt(name+"/startPos/y")),
           Vector2f(GameData::getInstance().getXmlInt(name+"/startVel/x"),
                    GameData::getInstance().getXmlInt(name+"/startVel/y")),
           Vector2f(GameData::getInstance().getXmlInt(name+"/minPosBoundary/x"),
                    GameData::getInstance().getXmlInt(name+"/minPosBoundary/y")),
           Vector2f(GameData::getInstance().getXmlInt(name+"/maxPosBoundary/x"),
                    GameData::getInstance().getXmlInt(name+"/maxPosBoundary/y"))
           ),
  image( RenderContext::getInstance()->getImage(name) ),
  backgroundWidth(GameData::getInstance().getXmlInt("background/width")),
  backgroundHeight(GameData::getInstance().getXmlInt("background/height"))
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s),
  image(s.image),
  backgroundWidth(GameData::getInstance().getXmlInt("background/width")),
  backgroundHeight(GameData::getInstance().getXmlInt("background/height"))
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  Drawable::operator=( rhs );
  image = rhs.image;
  backgroundWidth = rhs.backgroundWidth;
  backgroundHeight = rhs.backgroundHeight;
  return *this;
}

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void Sprite::draw() const {
  if(getScale() < SCALE_EPSILON) return;
  image->draw(getPositionX(), getPositionY(), getScale());
}

void Sprite::update(Uint32 ticks) {
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getPositionY() < getMinPosBoundaryY()) {
    setVelocityY( std::abs( getVelocityY() ) );
  }
  if ( getPositionY() > getMaxPosBoundaryY()-getScaledHeight()) {
    setVelocityY( -std::abs( getVelocityY() ) );
  }

  if ( getPositionX() < getMinPosBoundaryX()) {
    setVelocityX( std::abs( getVelocityX() ) );
  }
  if ( getPositionX() > getMaxPosBoundaryX()-getScaledWidth()) {
    setVelocityX( -std::abs( getVelocityX() ) );
  }
}
