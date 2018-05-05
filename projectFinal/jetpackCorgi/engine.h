#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "clock.h"
#include "hudMain.h"
#include "hudObjPool.h"
#include "gameOver.h"
#include "gameStart.h"
#include "hudTip.h"
#include "healthBar.h"
#include "background.h"
#include "viewport.h"
#include "renderContext.h"
#include "sound.h"

class Player;
class DumbSprite;
class SmartSprite;
class FallingSprite;
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  bool play();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

private:
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;
  HudMain& hudMain;
  HudObjPool& hudObjPool;
  HudTip& hudTip;
  HealthBar& healthBar;
  GameOver& gameOver;
  GameStart& gameStart;
  Viewport& viewport;
  SDL_Sound& sound;
  SDL_Renderer * const renderer;

  Background Sky;
  Background BackMtns;
  Background FrontMtns;
  Background Road;

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
