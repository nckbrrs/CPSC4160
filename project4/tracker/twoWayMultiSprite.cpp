#include "twoWayMultiSprite.h"
#include "gamedata.h"
#include "renderContext.h"

void TwoWayMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
		if (getVelocityX() > 0) {
	    currentFrame = (currentFrame+1) % numLeftFrames;
		}
		else {
			currentFrame = numLeftFrames + (currentFrame+1) % numRightFrames;
		}
		timeSinceLastFrame = 0;
	}
}

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
	         Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  images( RenderContext::getInstance()->getImages(name) ),

  currentFrame(0),
	numLeftFrames( Gamedata::getInstance().getXmlInt(name+"/leftFrames") ),
	numRightFrames( Gamedata::getInstance().getXmlInt(name+"/rightFrames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
	timeSinceLastFrame(0),
  backgroundWidth(Gamedata::getInstance().getXmlInt("background/width")),
  backgroundHeight(Gamedata::getInstance().getXmlInt("background/height"))
{ }

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& s) :
  Drawable(s),
  images(s.images),
  currentFrame(s.currentFrame),
	numLeftFrames(s.numLeftFrames),
	numRightFrames(s.numRightFrames),
	frameInterval(s.frameInterval),
	timeSinceLastFrame(s.timeSinceLastFrame),
  backgroundWidth( s.backgroundWidth ),
  backgroundHeight( s.backgroundHeight )
  { }

TwoWayMultiSprite& TwoWayMultiSprite::operator=(const TwoWayMultiSprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  currentFrame = (s.currentFrame);
	numLeftFrames = (s.numLeftFrames);
	numRightFrames = (s.numRightFrames);
	frameInterval = (s.frameInterval);
	timeSinceLastFrame = (s.timeSinceLastFrame);
  backgroundWidth = ( s.backgroundWidth );
  backgroundHeight = ( s.backgroundHeight );
  return *this;
}

void TwoWayMultiSprite::draw() const {
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWayMultiSprite::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > backgroundHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > backgroundWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }

}
