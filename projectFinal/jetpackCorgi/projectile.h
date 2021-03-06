#include "sprite.h"
#include "dumbSprite.h"
#include "gameData.h"
#include "vector2f.h"

class Projectile : public DumbSprite {
public:
  Projectile(const string& name) :
    DumbSprite(name),
    startingPos(getPosition()),
    distance(0),
    maxDistance(GameData::getInstance().getXmlInt(name+"/maxDistance")),
    tooFar(false)
  { }

  Projectile(const Projectile& s) :
    DumbSprite(s),
    startingPos(s.startingPos),
    distance(s.distance),
    maxDistance(s.maxDistance),
    tooFar(s.tooFar)
  { }

  virtual void update(Uint32 ticks);
  void collide() { setPosition(Vector2f(-200, -200)); setVelocity(Vector2f(0, 0)); }
  bool isTooFar() const { return tooFar; }
  void setStartingPos(const Vector2f& v) { startingPos = v; }
  void reset() {
    tooFar = false;
    distance = 0;
  }

private:
  Vector2f startingPos;
  float distance;
  float maxDistance;
  bool tooFar;
};
