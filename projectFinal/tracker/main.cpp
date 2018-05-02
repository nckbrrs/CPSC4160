// Nick Barrs
// CPSC 4160
// Data-Driven Object-Oriented Game Construction
// Spring 2018

#include "engine.h"
#include <time.h>

RenderContext* RenderContext::instance = NULL;

int main(int, char*[]) {
  srand(time(NULL));
  bool keepPlaying = true;
   try {
     while (keepPlaying) {
       Engine* engine = new Engine;
       keepPlaying = engine->play();
       delete engine;
       Clock::getInstance().startClock();
       SDL_Sound::getInstance().startMusic();
       HudMain::getInstance().setVisibility(false);
       HudObjPool::getInstance().setVisibility(false);
       HudTip::getInstance().setVisibility(false);
       GameStart::getInstance().setVisibility(true);
       HealthBar::getInstance().reset();
     }
     delete RenderContext::getInstance();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
