#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "clock.h"
#include "background.h"
#include "viewport.h"
#include "renderContext.h"
#include "sound.h"

class Player;
class DumbSprite;
class SmartSprite;
class FallingSprite;
class CollisionStrategy;
class Hud;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

private:
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;
  Hud& hud;
  SDL_Renderer * const renderer;
  SDL_Sound sound;

  Background Sky;
  Background BackMtns;
  Background FrontMtns;
  Background Road;
  Viewport& viewport;

  Player* player;
  std::vector<FallingSprite*> farFallingSprites;
  std::vector<FallingSprite*> middleFallingSprites;
  std::vector<FallingSprite*> closeFallingSprites;
  std::vector<DumbSprite*> dumbSprites;
  std::vector<SmartSprite*> smartSprites;
  CollisionStrategy* collisionStrategy;

  void draw() const;
  void update(Uint32);
  void checkForCollisions();
};
