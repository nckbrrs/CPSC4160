#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "gameData.h"
#include "engine.h"
#include "dumbSprite.h"
#include "smartSprite.h"
#include "player.h"

Engine::~Engine() {
  delete player;
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  Sky("Sky", GameData::getInstance().getXmlInt("Sky/factor") ),
  BackMtns("BackMtns", GameData::getInstance().getXmlInt("BackMtns/factor") ),
  FrontMtns("FrontMtns", GameData::getInstance().getXmlInt("FrontMtns/factor") ),
  Road("Road", GameData::getInstance().getXmlInt("Road/factor") ),
  viewport( Viewport::getInstance() ),
  player(new Player("JetpackStickman")),
  dumbSprites(),
  smartSprites()
{
  int n = GameData::getInstance().getXmlInt("numEvilJetpackStickmans");
  smartSprites.reserve(n);
  for (int i=0; i<n; i++) {
    smartSprites.push_back(new SmartSprite("EvilJetpackStickman", player));
    player->attach(smartSprites[i]);
  }
  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  Sky.draw();
  BackMtns.draw();
  FrontMtns.draw();
  Road.draw();
  player->draw();
  for (const SmartSprite* s : smartSprites) {
    s->draw();
  }
  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  player->update(ticks);
  Sky.update();
  BackMtns.update();
  FrontMtns.update();
  Road.update();
  for (SmartSprite* s : smartSprites) {
    s->update(ticks);
  }
  viewport.update();
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
      }
    }

    // In this section of the event loop we allow key bounce:
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A]) {
        static_cast<Player*>(player)->moveLeft();
      }
      if (keystate[SDL_SCANCODE_D]) {
        static_cast<Player*>(player)->moveRight();
      }
      if (keystate[SDL_SCANCODE_W]) {
        static_cast<Player*>(player)->moveUp();
      }
      if (keystate[SDL_SCANCODE_S]) {
        static_cast<Player*>(player)->moveDown();
      }
      draw();
      update(ticks);
    }
  }
}
