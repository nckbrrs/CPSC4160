#include <iostream>
#include <string>
#include "myTriangle.h"

MyTriangle::MyTriangle(SDL_Renderer* rend, Vector2f v0, Vector2f v1, Vector2f v2, SDL_Color col) :
  renderer(rend),
  vec0(v0),
  vec1(v1),
  vec2(v2),
  color(col) {}

void MyTriangle::drawTriangle() {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(renderer, vec0[0], vec0[1], vec1[0], vec1[1]);
  SDL_RenderDrawLine(renderer, vec1[0], vec1[1], vec2[0], vec2[1]);
  SDL_RenderDrawLine(renderer, vec2[0], vec2[1], vec0[0], vec0[1]);

  float x = smallest(vec0[0],vec1[0],vec2[0]);
  float y = smallest(vec0[1],vec1[1],vec2[1]);
  Vector2f box0( x, y );

  x = largest(vec0[0],vec1[0],vec2[0]);
  y = largest(vec0[1],vec1[1],vec2[1]);
  Vector2f box1( x, y );

  for (int x = box0[0]; x <= box1[0]; ++x) {
    for (int y = box0[1]; y <= box1[1]; ++y) {
      Vector2f p(x, y);
      if (triangle(p, 0.6)) {
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
}

float MyTriangle::wedge(Vector2f a, Vector2f b) {
  return a[0]*b[1] - a[1]*b[0];
}

float MyTriangle::triangle(Vector2f x, float fuzz) {
  Vector2f e0 = vec1 - vec0;
  Vector2f e1 = vec2 - vec1;
  Vector2f e2 = vec0 - vec2;
  float N = wedge(e1, -e0);
  if(N <= -0.00001){
      N  *= -1.0;
      e0 *= -1.0;
      e1 *= -1.0;
      e2 *= -1.0;
  }

  float b0 = wedge(e0, x - vec0);
  if(b0 <= -0.00001) { return 0.0; }
  float b1 = wedge(e1, x - vec1);
  if(b1 <= -0.00001) { return 0.0; }
  float b2 = wedge(e2, x - vec2);
  if(b2 <= -0.00001) { return 0.0; }
  if(fuzz == 0.0) return 1.0;
  return std::min(1.0, (pow(b0*b1*b2, 0.33) * 3.0 / N) / fuzz);
}

int MyTriangle::smallest(int a, int b, int c) {
  int temp = std::min(a, b);
  return std::min(temp, c);
}

int MyTriangle::largest(int a, int b, int c) {
  int temp = std::max(a, b);
  return std::max(temp, c);
}

Vector2f MyTriangle::getVec0() const {
  return vec0;
}

Vector2f MyTriangle::getVec1() const {
  return vec1;
}

Vector2f MyTriangle::getVec2() const {
  return vec2;
}

SDL_Color MyTriangle::getColor() const {
  return color;
}
