#include <string>
#include <SDL.h>
#include "vector2f.h"

class MyTriangle {
public:
  MyTriangle(SDL_Renderer*, Vector2f, Vector2f, Vector2f, SDL_Color);
  void drawTriangle();
  float wedge(Vector2f, Vector2f);
  float triangle(Vector2f, float);
  int smallest(int, int, int);
  int largest(int, int, int);
  /* IMPLEMENT THESE
  void getVec0();
  void getVec1();
  void getVec2();
  void getColor();
  */
private:
  SDL_Renderer* const renderer;
  const Vector2f vec0;
  const Vector2f vec1;
  const Vector2f vec2;
  const SDL_Color color;
};
