#include <string>
#include <SDL.h>

class MyCircle {
public:
  MyCircle(SDL_Renderer*, SDL_Point, int, SDL_Color);
  void drawCircle();
  /* IMPLEMENT THESE
  void getCenter();
  void getRadius();
  void getColor();
  */
private:
  SDL_Renderer* const renderer;
  const SDL_Point center;
  const int radius;
  const SDL_Color color;
  MyCircle(const MyCircle&);
};
