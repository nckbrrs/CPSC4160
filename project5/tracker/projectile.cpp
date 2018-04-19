#include <cmath>
#include "projectile.h"

void Projectile::update(Uint32 ticks) {
  DumbSprite::update(ticks);
  distance = (hypot(getPositionX()-startingPos[0], getPositionY()-startingPos[1]));
  if (distance > maxDistance) tooFar = true;
}
