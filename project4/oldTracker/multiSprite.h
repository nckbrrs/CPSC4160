#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&);
  MultiSprite(const MultiSprite&);
  virtual ~MultiSprite() { }

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { return images[currentFrame]; }
  virtual const SDL_Surface* getSurface() const { return images[currentFrame]->getSurface(); }

  int getScaledWidth() const { return getScale()*images[currentFrame]->getWidth(); }
  int getScaledHeight() const { return getScale()*images[currentFrame]->getHeight(); }

  unsigned getCurrentFrame() const { return currentFrame; }
  unsigned getNumFrames() const { return numFrames; }
  unsigned getFrameInterval() const { return frameInterval; }
  bool isTwoWay() const { return twoWay; }
  float getTimeSinceLastFrame() const { return timeSinceLastFrame; }
  int getBackgroundWidth() const { return backgroundWidth; }
  int getBackgroundHeight() const { return backgroundHeight; }

protected:
  std::vector<Image *> images;

  unsigned currentFrame;
  unsigned numFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  bool twoWay;
  int backgroundWidth;
  int backgroundHeight;

  virtual void advanceFrame(Uint32 ticks);
  MultiSprite& operator=(const MultiSprite&);
};
#endif
