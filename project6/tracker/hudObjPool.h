#ifndef HUDOBJPOOL__H
#define HUDOBJPOOL__H

#include <iostream>
#include <string>
#include <SDL.h>
#include "vector2f.h"

class HudObjPool {
public:
  static HudObjPool& getInstance();
  bool isVisible() const { return visible; }
  void setVisibility(bool v) { visible = v; }
  void draw(int, int);

private:
  int width;
  int height;
  Vector2f pos;
  bool visible;
  SDL_Color backgroundColor;
  SDL_Color outlineColor;
  SDL_Color textColor;

  HudObjPool();
  HudObjPool(const HudObjPool&);
  HudObjPool& operator=(const HudObjPool&);
};
#endif
