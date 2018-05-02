#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "sprite.h"
#include "gameData.h"

class Viewport {
public:
  static Viewport& getInstance();
  void draw(bool, int) const;
  void update();

  Vector2f getPosition() const { return position; }
  float getPositionX() const  { return position[0]; }
  void  setPositionX(float x) { position[0] = x; }
  float getPositionY() const  { return position[1]; }
  void  setPositionY(float y) { position[1] = y; }

  void setObjectToTrack(const Sprite *obj);
  const Sprite* getObjectToTrack() const { return objectToTrack; }

private:
  const GameData& gdata;
  Vector2f position;
  int backgroundWidth;
  int backgroundHeight;
  int viewWidth;
  int viewHeight;
  int objWidth;
  int objHeight;

  const Sprite *objectToTrack;

  Viewport();
  Viewport(const Viewport&);
  Viewport& operator=(const Viewport&);
};
#endif
