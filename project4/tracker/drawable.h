#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>
#include <string>
#include "vector2f.h"
#include "image.h"

// Drawable is an Abstract Base Class (ABC) that specifies the methods
// that derived classes may or must have.
class Drawable {
public:
  Drawable(const std::string& n,
           const Vector2f& pos,
           const Vector2f& vel,
           const Vector2f& minPosB,
           const Vector2f& maxPosB):
    name(n),
    position(pos),
    velocity(vel),
    minPosBoundary(minPosB),
    maxPosBoundary(maxPosB),
    scale(1.0)
  { }

  Drawable(const Drawable& s):
    name(s.name),
    position(s.position),
    velocity(s.velocity),
    minPosBoundary(s.minPosBoundary),
    maxPosBoundary(s.maxPosBoundary),
    scale(1.0)
  { }

  virtual ~Drawable() {}

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;

  float getScale() const  { return scale; }
  void  setScale(float s) { scale = s; }
  virtual int getScaledWidth() const = 0;
  virtual int getScaledHeight() const = 0;
  virtual const SDL_Surface* getSurface() const = 0;

  const std::string& getName() const { return name; }
  void setName(const std::string& n) { name = n;    }

  virtual const Image* getImage() const = 0;

  const Vector2f& getVelocity() const    { return velocity; }
  void  setVelocity(const Vector2f& vel) { velocity = vel;  }
  const Vector2f& getPosition() const    { return position; }
  void  setPosition(const Vector2f& pos) { position = pos;  }

  float getPositionX() const  { return position[0]; }
  void  setPositionX(float x) { position[0] = x;    }
  float getPositionY() const  { return position[1]; }
  void  setPositionY(float y) { position[1] = y;    }

  float getVelocityX() const   { return velocity[0]; }
  void  setVelocityX(float vx) { velocity[0] = vx;   }
  float getVelocityY() const   { return velocity[1]; }
  void  setVelocityY(float vy) { velocity[1] = vy;   }

  int  getMinPosBoundaryX() const  { return minPosBoundary[0]; }
  void setMinPosBoundaryX(float x) { minPosBoundary[0] = x;    }
  int  getMinPosBoundaryY() const  { return minPosBoundary[1]; }
  void setMinPosBoundaryY(float y) { minPosBoundary[1] = y;    }

  int  getMaxPosBoundaryX() const  { return maxPosBoundary[0]; }
  void setMaxPosBoundaryX(float x) { maxPosBoundary[0] = x;    }
  int  getMaxPosBoundaryY() const  { return maxPosBoundary[1]; }
  void setMaxPosBoundaryY(float y) { maxPosBoundary[1] = y;    }

private:
  std::string name;
  Vector2f position;
  Vector2f velocity;
  Vector2f minPosBoundary;
  Vector2f maxPosBoundary;
  float scale;
};
#endif
