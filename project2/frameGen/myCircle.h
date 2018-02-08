#include <string>
#include <SDL.h>

class MyCircle {
public:
  MyCircle(SDL_Renderer*, SDL_Point, int, SDL_Color);
  void drawCircle();
  SDL_Point getCenter() const;
  int getRadius() const;
  SDL_Color getColor() const;
private:
  SDL_Renderer* const renderer;
  const SDL_Point center;
  const int radius;
  const SDL_Color color;
};
