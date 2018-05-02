#include <sstream>
#include "viewport.h"
#include "ioMod.h"

Viewport& Viewport::getInstance() {
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() :
  gdata(GameData::getInstance()),
  position(0, 0),
  backgroundWidth(gdata.getXmlInt("background/width")),
  backgroundHeight(gdata.getXmlInt("background/height")),
  viewWidth(gdata.getXmlInt("view/width")),
  viewHeight(gdata.getXmlInt("view/height")),
  objWidth(0), objHeight(0),
  objectToTrack(NULL)
{}

void Viewport::setObjectToTrack(const Sprite *obj) {
  objectToTrack = obj;
  objWidth = objectToTrack->getScaledWidth();
  objHeight = objectToTrack->getScaledHeight();
}

void Viewport::draw(int numCatsLeft) const {
  SDL_Color black = {static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(255)};

  // drop shadow
  IoMod::getInstance().writeText("NICK BARRS",
    gdata.getXmlInt("text/name/locX")-1,
    gdata.getXmlInt("text/name/locY")+1,
    black);

  // regular text
  IoMod::getInstance().writeText("NICK BARRS",
    gdata.getXmlInt("text/name/locX"),
    gdata.getXmlInt("text/name/locY"));

  // drop shadow
  IoMod::getInstance().writeText("CATS REMAINING: " + std::to_string(numCatsLeft),
    gdata.getXmlInt("text/catsRemaining/locX")-1,
    gdata.getXmlInt("text/catsRemaining/locY")+1,
    black);

  // regular text
  IoMod::getInstance().writeText("CATS REMAINING: " + std::to_string(numCatsLeft),
    gdata.getXmlInt("text/catsRemaining/locX"),
    gdata.getXmlInt("text/catsRemaining/locY"));
}

void Viewport::update() {
  const float x = objectToTrack->getPositionX();
  const float y = objectToTrack->getPositionY();

  position[0] = (x + objWidth/2) - viewWidth/2;
  position[1] = (y + objHeight/2) - viewHeight/2;
  if (position[0] < 0) position[0] = 0;
  if (position[1] < 0) position[1] = 0;
  if (position[0] > (backgroundWidth - viewWidth)) {
    position[0] = backgroundWidth-viewWidth;
  }
  if (position[1] > (backgroundHeight - viewHeight)) {
    position[1] = backgroundHeight-viewHeight;
  }
}
