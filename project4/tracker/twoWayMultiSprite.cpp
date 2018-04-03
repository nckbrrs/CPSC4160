#include "twoWayMultiSprite.h"
#include "gameData.h"
#include "renderContext.h"

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& name) :
  MultiSprite(name),
	numLeftFrames(GameData::getInstance().getXmlInt(name+"/leftFrames")),
	numRightFrames(GameData::getInstance().getXmlInt(name+"/rightFrames"))
{ }

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& s) :
  MultiSprite(s),
	numLeftFrames(s.numLeftFrames),
	numRightFrames(s.numRightFrames)
{ }

TwoWayMultiSprite& TwoWayMultiSprite::operator=(const TwoWayMultiSprite& s) {
  MultiSprite::operator=(s);
	numLeftFrames = (s.numLeftFrames);
	numRightFrames = (s.numRightFrames);
  return *this;
}

void TwoWayMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
		if (getVelocityX() >= 0) currentFrame = (currentFrame+1) % numLeftFrames;
		else currentFrame = numLeftFrames + ((currentFrame+1) % numRightFrames);
		timeSinceLastFrame = 0;
	}
}
