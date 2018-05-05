#include <iostream>
#include <string>
#include "myCircle.h"

MyCircle::MyCircle(SDL_Renderer* rend, SDL_Point cen, int rad, SDL_Color col) :
  renderer(rend),
  center(cen),
  radius(rad),
  color(col) {}

void MyCircle::drawCircle() {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w;
      int dy = radius - h;
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

SDL_Point MyCircle::getCenter() const {
  return center;
}

int MyCircle::getRadius() const {
  return radius;
}

SDL_Color MyCircle::getColor() const {
  return color;
}
