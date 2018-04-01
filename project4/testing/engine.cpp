#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "gamedata.h"
#include "engine.h"

Engine::~Engine() {
  std::vector<Sprite*>().swap(sprites);
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  Sky("Sky", Gamedata::getInstance().getXmlInt("Sky/factor") ),
  BackMtns("BackMtns", Gamedata::getInstance().getXmlInt("BackMtns/factor") ),
  FrontMtns("FrontMtns", Gamedata::getInstance().getXmlInt("FrontMtns/factor") ),
  Road("Road", Gamedata::getInstance().getXmlInt("Road/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),
  makeVideo( false )
{
  for (int i = 0; i < Gamedata::getInstance().getXmlInt("numStickmans"); i++) {
    sprites.push_back(new Sprite("Stickman"));
  }
  for (int i = 0; i < Gamedata::getInstance().getXmlInt("numClouds"); i++) {
    sprites.push_back(new Sprite("Cloud"));
  }
  Viewport::getInstance().setObjectToTrack(sprites[0]);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  Sky.draw();
  BackMtns.draw();
  FrontMtns.draw();
  Road.draw();

  for (int i = 0; i < (int)sprites.size(); i++) {
    sprites[i]->draw();
  }

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for (int i = 0; i < (int)sprites.size(); i++) {
    sprites[i]->update(ticks);
  }

  Sky.update();
  BackMtns.update();
  FrontMtns.update();
  Road.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
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
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
      }
    }

    // In this section of the event loop we allow key bounce:
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
    }
  }
}
