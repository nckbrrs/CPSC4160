#include "multiSprite.h"
#include "gameData.h"
#include "renderContext.h"

MultiSprite::MultiSprite( const std::string& name) :
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
  images( RenderContext::getInstance()->getImages(name) ),

  currentFrame(0),
  numberOfFrames( GameData::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( GameData::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame(0),
  backgroundWidth(GameData::getInstance().getXmlInt("background/width")),
  backgroundHeight(GameData::getInstance().getXmlInt("background/height"))
{ }

MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s),
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfFrames(s.numberOfFrames),
  frameInterval(s.frameInterval),
  timeSinceLastFrame( s.timeSinceLastFrame),
  backgroundWidth(s.backgroundWidth),
  backgroundHeight(s.backgroundHeight)
{ }

MultiSprite& MultiSprite::operator=(const MultiSprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfFrames = (s.numberOfFrames);
  frameInterval = (s.frameInterval);
  timeSinceLastFrame = (s.timeSinceLastFrame);
  backgroundWidth = (s.backgroundWidth);
  backgroundHeight = (s.backgroundHeight);
  return *this;
}

void MultiSprite::draw() const {
  images[currentFrame]->draw(getPositionX(), getPositionY(), getScale());
}

void MultiSprite::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getPositionY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getPositionY() > backgroundHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getPositionX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getPositionX() > backgroundWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }
}

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}
