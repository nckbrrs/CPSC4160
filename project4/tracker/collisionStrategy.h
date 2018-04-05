#include <cmath>
#include "sprite.h"

class CollisionStrategy {
public:
  virtual bool execute(const Sprite&, const Sprite&) const = 0;
  virtual void draw() const = 0;
  virtual ~CollisionStrategy() { }
};

class RectangularCollisionStrategy : public CollisionStrategy {
public:
  RectangularCollisionStrategy() {}
  virtual bool execute(const Sprite&, const Sprite&) const;
  virtual void draw() const;
};

class MidpointCollisionStrategy : public CollisionStrategy {
public:
  MidpointCollisionStrategy() {}
  virtual bool execute(const Sprite&, const Sprite&) const;
  virtual void draw() const;
  float distance(float, float, float, float) const;
};

class PerPixelCollisionStrategy : public CollisionStrategy {
public:
  PerPixelCollisionStrategy() {}
  virtual bool execute(const Sprite&, const Sprite&) const;
  virtual void draw() const;
private:
  bool isVisible(Uint32, SDL_Surface*) const;
};
