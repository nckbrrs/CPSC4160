#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "myCircle.h"
#include "vector2f.h"
#include "myTriangle.h"

const std::string NAME = "nbarrs";
const int WIDTH = 640;
const int HEIGHT = 480;

/*
std::ostream& operator<<(std::ostream& out, const MyCircle& c) {
  out << "CIRCLE -- Center: " << c.getCenter() << ", ";
  out << "Radius: " << c.getRadius() << ", ";
  out << "Color: " << c.getColor() << std::endl;
  return out;
}

std::ostream& operator<<(std::ostream& out, const MyTriangle& t) {
  out << "TRIANGLE -- Vec0: " << t.getVec0() << ", ";
  out << "Vec1: " << t.getVec1() << ", ";
  out << "Vec2: " << t.getVec2() << ", ";
  out << "Color: " << t.getColor() << std::endl;
  return out;
}
*/

int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer );

  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);

  SDL_Color red = {255,0,0,255};
  SDL_Color black = {0, 0, 0, 255};
  SDL_Color blue = {0, 0, 255, 255};

  SDL_Point headCenter = {320, 240};
  MyCircle head(renderer, headCenter, 200, red);
  head.drawCircle();

  SDL_Point leftEyeCenter = {260, 180};
  MyCircle leftEye(renderer, leftEyeCenter, 10, black);
  leftEye.drawCircle();

  SDL_Point rightEyeCenter = {380, 180};
  MyCircle rightEye(renderer, rightEyeCenter, 10, black);
  rightEye.drawCircle();

  Vector2f v0(0, 0);
  Vector2f v1(320, 480);
  Vector2f v2(640, 0);
  MyTriangle triangle(renderer, v0, v1, v2, blue);
  triangle.drawTriangle();

  SDL_RenderPresent(renderer);
  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
  frameGen.makeFrame();

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
