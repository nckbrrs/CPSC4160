#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multiSprite.h"
#include "twoWayMultiSprite.h"
#include "player.h"
#include "gameData.h"
#include "engine.h"

Engine::~Engine() {
  nonPlayerSprites.clear();
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
  nonPlayerSprites(),
  makeVideo( false )
{
  player = new Player("Stickman");

  for (int i = 0; i < GameData::getInstance().getXmlInt("numClouds"); i++) {
    nonPlayerSprites.push_back(new Sprite("Cloud"));
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

  for (int i = 0; i < (int)nonPlayerSprites.size(); i++) {
    nonPlayerSprites[i]->draw();
  }

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  player->update(ticks);

  for (int i = 0; i < (int)nonPlayerSprites.size(); i++) {
    nonPlayerSprites[i]->update(ticks);
  }

  Sky.update();
  BackMtns.update();
  FrontMtns.update();
  Road.update();
  viewport.update(); // always update viewport last
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
