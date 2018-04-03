#include <sstream>
#include "viewport.h"
#include "ioMod.h"
#include "clock.h"

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

void Viewport::setObjectToTrack(const Drawable *obj) {
  objectToTrack = obj;
  objWidth = objectToTrack->getScaledWidth();
  objHeight = objectToTrack->getScaledHeight();
}

void Viewport::draw() const {
  /* color that "tracking" text will be printed in
  SDL_Color trackingColor = {static_cast<Uint8>(gdata.getXmlInt("text/tracking/font/red")),
                        static_cast<Uint8>(gdata.getXmlInt("text/tracking/font/green")),
                        static_cast<Uint8>(gdata.getXmlInt("text/tracking/font/blue")),
                        static_cast<Uint8>(gdata.getXmlInt("text/tracking/font/alpha"))};
  */

  /* color that "fps" text will be printed in
  SDL_Color fpsColor = {static_cast<Uint8>(gdata.getXmlInt("text/fps/font/red")),
                        static_cast<Uint8>(gdata.getXmlInt("text/fps/font/green")),
                        static_cast<Uint8>(gdata.getXmlInt("text/fps/font/blue")),
                        static_cast<Uint8>(gdata.getXmlInt("text/fps/font/alpha"))};
  */

  SDL_Color nameColor = {static_cast<Uint8>(gdata.getXmlInt("text/name/font/red")),
                        static_cast<Uint8>(gdata.getXmlInt("text/name/font/green")),
                        static_cast<Uint8>(gdata.getXmlInt("text/name/font/blue")),
                        static_cast<Uint8>(gdata.getXmlInt("text/name/font/alpha"))};

  /* print which object is being tracked
  IoMod::getInstance().
    writeText("Tracking: "+objectToTrack->getName(),
              gdata.getXmlInt("text/tracking/locX"),
              gdata.getXmlInt("text/tracking/locY"),
              trackingColor);
  */

  /* print FPS
  std::ostringstream fpsStream;
  fpsStream << "FPS: " << Clock::getInstance().getFps() << std::endl;
  IoMod::getInstance().
    writeText(fpsStream.str(),
              gdata.getXmlInt("text/fps/locX"),
              gdata.getXmlInt("text/fps/locY"),
              fpsColor);
  */

  /* print name */
  IoMod::getInstance().
    writeText("Nick Barrs",
              gdata.getXmlInt("text/name/locX"),
              gdata.getXmlInt("text/name/locY"),
              nameColor);
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
