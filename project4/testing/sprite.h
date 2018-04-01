#ifndef SPRITE__H
#define SPRITE__H
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "vector2f.h"
#include "image.h"

class Sprite {
public:
  Sprite(const std::string&);
  Sprite(const Sprite&);
  ~Sprite() {}

  void draw() const;
  void update(Uint32 ticks);

  float getScale() const  { return scale; }
  void  setScale(float s) { scale = s; }

  float getX() const  { return position[0]; }
  void  setX(float x) { position[0] = x;    }

  float getY() const  { return position[1]; }
  void  setY(float y) { position[1] = y;    }

  const Vector2f& getVelocity() const    { return velocity; }
  void  setVelocity(const Vector2f& vel) { velocity = vel;  }

  const Vector2f& getPosition() const    { return position; }
  void  setPosition(const Vector2f& pos) { position = pos;  }

  float getVelocityX() const   { return velocity[0]; }
  void  setVelocityX(float vx) { velocity[0] = vx;   }

  float getVelocityY() const   { return velocity[1]; }
  void  setVelocityY(float vy) { velocity[1] = vy;   }

  const std::string& getName() const { return name; }
  void setName(const std::string& n) { name = n; }

  int getScaledWidth() const {
    return getScale()*images[currentFrame]->getWidth();
  }
  int getScaledHeight() const {
    return getScale()*images[currentFrame]->getHeight();
  }
  const Image* getImage() const {
    return images[currentFrame];
  }
  const SDL_Surface* getSurface() const {
    return images[currentFrame]->getSurface();
  }

private:
  std::string name;
  Vector2f position;
  Vector2f velocity;
  float scale;
  std::vector<Image *> images;
  unsigned currentFrame;
  unsigned numLeftFrames;
  unsigned numRightFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int backgroundWidth;
  int backgroundHeight;

  void advanceFrame(Uint32 ticks);
  Sprite& operator=(const Sprite&);
};
#endif
