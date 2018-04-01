#include "sprite.h"
#include "gamedata.h"
#include "renderContext.h"

void Sprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
		if (getVelocityX() > 0) {
	    currentFrame = (currentFrame+1) % numLeftFrames;
		}
		else {
			currentFrame = numLeftFrames + ((currentFrame+1) % numRightFrames);
		}
		timeSinceLastFrame = 0;
	}
}

/*
Vector2f Sprite::makeVelocity(int vx, int vy) const {
  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();

  return Vector2f(newvx, newvy);
}*/

Sprite::Sprite( const std::string& name) :
  name(name),
	position(Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y"))),
	velocity(Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))),
	scale(1.0),
  images( RenderContext::getInstance()->getImages(name) ),
  currentFrame(0),
	numLeftFrames( Gamedata::getInstance().getXmlInt(name+"/leftFrames") ),
	numRightFrames( Gamedata::getInstance().getXmlInt(name+"/rightFrames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
	timeSinceLastFrame(0),
  backgroundWidth(Gamedata::getInstance().getXmlInt("background/width")),
  backgroundHeight(Gamedata::getInstance().getXmlInt("background/height"))
{ }

Sprite::Sprite(const Sprite& s) :
  name(s.name),
	position(s.position),
	velocity(s.velocity),
	scale(s.scale),
  images(s.images),
  currentFrame(s.currentFrame),
	numLeftFrames(s.numLeftFrames),
	numRightFrames(s.numRightFrames),
	frameInterval(s.frameInterval),
	timeSinceLastFrame(s.timeSinceLastFrame),
  backgroundWidth( s.backgroundWidth ),
  backgroundHeight( s.backgroundHeight )
  { }

Sprite& Sprite::operator=(const Sprite& s) {
	name = (s.name);
	position = (s.position);
	velocity = (s.velocity);
	scale = (s.scale);
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

void Sprite::draw() const {
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void Sprite::update(Uint32 ticks) {
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
