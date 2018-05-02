#ifndef HUDTIPPOOL__H
#define HUDTIPPOOL__H

#include <iostream>
#include <string>
#include <SDL.h>
#include "vector2f.h"

class HudTip {
public:
  static HudTip& getInstance();
  bool isVisible() const { return visible; }
  void setVisibility(bool v) { visible = v; }
  void draw();

private:
  int width;
  int height;
  Vector2f pos;
  bool visible;
  SDL_Color backgroundColor;
  SDL_Color outlineColor;
  SDL_Color textColor;

  HudTip();
  HudTip(const HudTip&);
  HudTip& operator=(const HudTip&);
};
#endif
