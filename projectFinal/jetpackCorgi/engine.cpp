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
#include "fallingSprite.h"
#include "player.h"
#include "collisionStrategy.h"

Engine::~Engine() {
  delete player;

  for (DumbSprite* ds : dumbSprites) {
    delete ds;
  }
  dumbSprites.clear();
  for (SmartSprite* ss : smartSprites) {
    delete ss;
  }
  smartSprites.clear();
  for (FallingSprite* fs : farFallingSprites) {
    delete fs;
  }
  farFallingSprites.clear();
  for (FallingSprite* fs : middleFallingSprites) {
    delete fs;
  }
  middleFallingSprites.clear();
  for (FallingSprite* fs : closeFallingSprites) {
    delete fs;
  }
  closeFallingSprites.clear();

  delete collisionStrategy;
  std::cout << "terminating program..." << std::endl;
}

Engine::Engine() :
  rc(RenderContext::getInstance()),
  io(IoMod::getInstance()),
  clock(Clock::getInstance()),
  hudMain(HudMain::getInstance()),
  hudObjPool(HudObjPool::getInstance()),
  hudTip(HudTip::getInstance()),
  healthBar(HealthBar::getInstance()),
  gameOver(GameOver::getInstance()),
  gameStart(GameStart::getInstance()),
  viewport(Viewport::getInstance()),
  sound(SDL_Sound::getInstance()),
  renderer(rc->getRenderer()),
  Sky("Sky", GameData::getInstance().getXmlInt("Sky/factor")),
  BackMtns("BackMtns", GameData::getInstance().getXmlInt("BackMtns/factor")),
  FrontMtns("FrontMtns", GameData::getInstance().getXmlInt("FrontMtns/factor")),
  Road("Road", GameData::getInstance().getXmlInt("Road/factor")),
  player(new Player("JetpackCorgi")),
  farFallingSprites(),
  middleFallingSprites(),
  closeFallingSprites(),
  dumbSprites(),
  smartSprites(),
  collisionStrategy(new MidpointCollisionStrategy)
{
  int i, n = GameData::getInstance().getXmlInt("numJetpackCats");
  smartSprites.reserve(n);
  for (i=0; i<n; i++) {
    smartSprites.push_back(new SmartSprite("JetpackCat", player));
    smartSprites.back()->randomizeVelocity();
    smartSprites.back()->randomizePosition();
    player->attach(smartSprites[i]);
  }

  n = GameData::getInstance().getXmlInt("numClouds");
  for (i=0; i<n; i++) {
    dumbSprites.push_back(new DumbSprite("Cloud"));
    dumbSprites.back()->randomizeVelocity();
    dumbSprites.back()->randomizePosition();
  }

  n = GameData::getInstance().getXmlInt("numDonuts");
  for (i=0; i<(int)(n*0.33); i++) {
    farFallingSprites.push_back(new FallingSprite("Donut"));
    farFallingSprites.back()->setScale(farFallingSprites.back()->getScale() * 0.5);
    farFallingSprites.back()->randomizePosition();
    farFallingSprites.back()->randomizeVelocity();
  }
  for (i=(int)(n*0.33); i<(int)(n*0.66); i++) {
    middleFallingSprites.push_back(new FallingSprite("Donut"));
    middleFallingSprites.back()->setScale(middleFallingSprites.back()->getScale() * 0.8);
    middleFallingSprites.back()->randomizePosition();
    middleFallingSprites.back()->randomizeVelocity();
  }
  for (i=(int)(n*0.66); i<n; i++) {
    closeFallingSprites.push_back(new FallingSprite("Donut"));
    closeFallingSprites.back()->randomizePosition();
    closeFallingSprites.back()->randomizeVelocity();
  }

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "loading complete!" << std::endl;
}

void Engine::draw() const {
  Sky.draw();
  for (const FallingSprite* s : farFallingSprites) s->draw();
  BackMtns.draw();
  for (const FallingSprite* s : middleFallingSprites) s->draw();
  FrontMtns.draw();
  for (const FallingSprite* s : closeFallingSprites) s->draw();
  Road.draw();
  for (const SmartSprite* s : smartSprites) s->draw();
  for (const DumbSprite* s : dumbSprites) s->draw();
  player->draw();
  hudMain.draw();
  hudObjPool.draw(player->getActiveProjectiles().size(), player->getFreeProjectiles().size());
  hudTip.draw();
  healthBar.draw(player->getPositionX(), player->getPositionY(), player->getScaledWidth(), player->getScaledHeight());
  gameStart.draw();
  viewport.draw(player->isGodMode(), smartSprites.size());
  if (player->getLivesLeft() <= 0) {
    hudMain.setVisibility(false);
    hudObjPool.setVisibility(false);
    hudTip.setVisibility(false);
    gameOver.setVisibility(true);
    gameOver.draw(false);

  }
  else if (smartSprites.size() <= 0) {
    hudMain.setVisibility(false);
    hudObjPool.setVisibility(false);
    hudTip.setVisibility(false);
    gameOver.setVisibility(true);
    gameOver.draw(true);
  }
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
    checkForCollisions();
    player->update(ticks);
    for (FallingSprite* s : farFallingSprites) s->update(ticks);
    for (FallingSprite* s : middleFallingSprites) s->update(ticks);
    for (FallingSprite* s : closeFallingSprites) s->update(ticks);
    for (SmartSprite* s : smartSprites) s->update(ticks);
    for (DumbSprite* s : dumbSprites) s->update(ticks);
    Sky.update();
    BackMtns.update();
    FrontMtns.update();
    Road.update();
    viewport.update();
}

void Engine::checkForCollisions() {
  auto smartIt = smartSprites.begin();
  while (smartIt != smartSprites.end()) {
    if (!(player->getActiveProjectiles().empty())) {
      for (auto proj : player->getActiveProjectiles()) {
        if (collisionStrategy->execute(*proj, **smartIt)) {
          (*smartIt)->collide();
          (*proj).collide();
        }
      }
    }
    if ((collisionStrategy->execute(*player, **smartIt)) && !(player->isColliding())) {
      player->collide();
    }
    if (player->hasCollided() && !(player->isColliding())) {
      player->loseLife();
      healthBar.setCurrentLength(healthBar.getCurrentLength() - (1.0 / player->getInitNumLives()));
      player->setCollided(false);
    }
    if ((*smartIt)->hasCollided() && (!((*smartIt)->isColliding()))) {
      SmartSprite* deadSmartSprite = *smartIt;
      player->detach(deadSmartSprite);
      smartIt = smartSprites.erase(smartIt);
      delete deadSmartSprite;
    } else {
      ++smartIt;;
    }
  }
}

bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();

  while (!done) {
    while (SDL_PollEvent(&event)) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if (keystate[SDL_SCANCODE_RETURN]) {
          if (gameStart.isVisible()) {
            gameStart.setVisibility(false);
            hudMain.setVisibility(true);
            hudObjPool.setVisibility(true);
            hudTip.setVisibility(true);
          }
        }
        if (keystate[SDL_SCANCODE_P]) {
          if (clock.isPaused()) clock.unpause();
          else clock.pause();
          sound.toggleMusic();
        }
        if (keystate[SDL_SCANCODE_F1]) {
          hudMain.setVisibility(!hudMain.isVisible());
          hudObjPool.setVisibility(!hudObjPool.isVisible());
          hudTip.setVisibility(!hudTip.isVisible());
        }
        if (keystate[SDL_SCANCODE_SPACE]) {
          player->shoot();
        }
        if (keystate[SDL_SCANCODE_M]) {
          sound.toggleMusic();
        }
        if (keystate[SDL_SCANCODE_R]) {
          clock.unpause();
          return true;
        }
        if (keystate[SDL_SCANCODE_G]) {
          player->toggleGodMode();
        }
      }
    }
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D]) {
        static_cast<Player*>(player)->moveLeft();
      }
      if (keystate[SDL_SCANCODE_D] && !keystate[SDL_SCANCODE_A]) {
        static_cast<Player*>(player)->moveRight();
      }
      if (keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S]) {
        static_cast<Player*>(player)->moveUp();
      }
      if (keystate[SDL_SCANCODE_S] && !keystate[SDL_SCANCODE_W]) {
        static_cast<Player*>(player)->moveDown();
      }
      draw();
      update(ticks);
    }
  }
  return false;
}
