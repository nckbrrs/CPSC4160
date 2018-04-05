#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "clock.h"
#include "background.h"
#include "viewport.h"
#include "renderContext.h"

class Player;
class DumbSprite;
class SmartSprite;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();

private:
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;
  SDL_Renderer * const renderer;
  Background Sky;
  Background BackMtns;
  Background FrontMtns;
  Background Road;
  Viewport& viewport;

  Player* player;
  std::vector<DumbSprite*> dumbSprites;
  std::vector<SmartSprite*> smartSprites;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  void printScales() const;
  void checkForCollisions();
};
