#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "myCircle.h"
#include "vector2f.h"
#include "myTriangle.h"

// vars
const std::string NAME = "nbarrs";
const int WIDTH = 640;
const int HEIGHT = 480;
const SDL_Color white = {255, 255, 255, 255};
const SDL_Color lavender = {230, 230, 250, 255};
const SDL_Color cyan = {0, 255, 255, 255};
const SDL_Color teal = {0, 128, 128, 255};
const SDL_Color sky = {135, 206, 250, 255};
const SDL_Point trueCenter = {320, 240};

// OVERLOAD OUTPUT OPERATOR FOR MYCIRCLE
std::ostream& operator<<(std::ostream& out, const MyCircle& c) {
  out << "CIRCLE" << std::endl;
  out << "Center: {" << c.getCenter().x << ", " << c.getCenter().y << "}" << std::endl;
  out << "Radius: " << c.getRadius() << std::endl;
  out << "Color: " << "{";
  out << (int)c.getColor().r << ", ";
  out << (int)c.getColor().g << ", ";
  out << (int)c.getColor().b << ", ";
  out << (int)c.getColor().a << "}" << std::endl;
  return out;
}

// OVERLOAD OUTPUT OPERATOR FOR MYCIRCLE
std::ostream& operator<<(std::ostream& out, const MyTriangle& t) {
  out << "TRIANGLE" << std::endl;
  out << "vec0: " << t.getVec0() << std::endl;
  out << "vec1: " << t.getVec1() << std::endl;
  out << "vec2: " << t.getVec2() << std::endl;
  out << "Color: " << "{";
  out << (int)t.getColor().r << ", ";
  out << (int)t.getColor().g << ", ";
  out << (int)t.getColor().b << ", ";
  out << (int)t.getColor().a << "}" << std::endl;
  return out;
}

int main(void) {
  // init
  SDL_Renderer *renderer;
  SDL_Window *window;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer( WIDTH, HEIGHT, 0, &window, &renderer);

  // clear with purple background
  SDL_SetRenderDrawColor( renderer, 123, 104, 238, 255);
  SDL_RenderClear(renderer);

  // draw white rectangle
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
  const SDL_Rect r1 = {5, 5, 625, 465};
  SDL_RenderDrawRect(renderer, &r1);
  for (int x=5; x<635; x++) {
    for (int y=5; y<475; y++) {
      SDL_RenderDrawPoint(renderer, x, y);
    }
  }

  // draw concentric background circles
  MyCircle c1(renderer, trueCenter, 225, sky);
  c1.drawCircle();
  std::cout << "c1: " << c1 << std::endl;

  MyCircle c2(renderer, trueCenter, 220, white);
  c2.drawCircle();
  std::cout << "c2: " << c2 << std::endl;

  MyCircle c3(renderer, trueCenter, 215, sky);
  c3.drawCircle();
  std::cout << "c3: " << c3 << std::endl;

  // draw three large primary triangles
  Vector2f t1v0(135, 330);
  Vector2f t1v1(295, 55);
  Vector2f t1v2(455, 330);
  MyTriangle t1(renderer, t1v0, t1v1, t1v2, cyan);
  t1.drawTriangle();
  std::cout << "t1: " << t1 << std::endl;

  Vector2f t2v0(160, 370);
  Vector2f t2v1(320, 95);
  Vector2f t2v2(480, 370);
  MyTriangle t2(renderer, t2v0, t2v1, t2v2, lavender);
  t2.drawTriangle();
  std::cout << "t2: " << t2 << std::endl;

  Vector2f t3v0(185, 330);
  Vector2f t3v1(345, 55);
  Vector2f t3v2(505, 330);
  MyTriangle t3(renderer, t3v0, t3v1, t3v2, teal);
  t3.drawTriangle();
  std::cout << "t3: " << t3 << std::endl;

  // draw three tiny triangles at "corners" to fill out connections
  Vector2f t4v0(135, 330);
  Vector2f t4v1(183, 330);
  Vector2f t4v2(160, 370);
  MyTriangle t4(renderer, t4v0, t4v1, t4v2, cyan);
  t4.drawTriangle();
  std::cout << "t4: " << t4 << std::endl;

  Vector2f t5v0(321, 96);
  Vector2f t5v1(295, 55);
  Vector2f t5v2(345, 55);
  MyTriangle t5(renderer, t5v0, t5v1, t5v2, teal);
  t5.drawTriangle();
  std::cout << "t5: " << t5 << std::endl;

  Vector2f t6v0(455, 331);
  Vector2f t6v1(505, 331);
  Vector2f t6v2(480, 370);
  MyTriangle t6(renderer, t6v0, t6v1, t6v2, lavender);
  t6.drawTriangle();
  std::cout << "t6: " << t6 << std::endl;

  // draw three medium triangles to construct the actual illustration
  Vector2f t7v0(320, 95);
  Vector2f t7v1(205, 290);
  Vector2f t7v2(435, 290);
  MyTriangle t7(renderer, t7v0, t7v1, t7v2, cyan);
  t7.drawTriangle();
  std::cout << "t7: " << t7 << std::endl;

  Vector2f t8v0(184, 330);
  Vector2f t8v1(295, 130);
  Vector2f t8v2(405, 330);
  MyTriangle t8(renderer, t8v0, t8v1, t8v2, lavender);
  t8.drawTriangle();
  std::cout << "t8: " << t8 << std::endl;

  Vector2f t9v0(235, 330);
  Vector2f t9v1(320, 172);
  Vector2f t9v2(405, 330);
  MyTriangle t9(renderer, t9v0, t9v1, t9v2, teal);
  t9.drawTriangle();
  std::cout << "t9: " << t9 << std::endl;

  // draw final middle triangle to imitate a "hole" in illustration
  Vector2f t10v0(255, 290);
  Vector2f t10v1(320, 172);
  Vector2f t10v2(385, 290);
  MyTriangle t10(renderer, t10v0, t10v1, t10v2, sky);
  t10.drawTriangle();
  std::cout << "t10: " << t10 << std::endl;

  // render drawing
  SDL_RenderPresent(renderer);
  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
  frameGen.makeFrame();

  // listen for exit
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

  // destroy drawing and close
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
