// Nick Barrs
// Data-Driven Object-Oriented Game Construction
#include "engine.h"

RenderContext* RenderContext::instance = NULL;

int main(int, char*[]) {
  bool keepPlaying = true;
   try {
     while (keepPlaying) {
       Engine* engine = new Engine;
       keepPlaying = engine->play();
       delete engine;
       Clock::getInstance().startClock();
       SDL_Sound::getInstance().startMusic();
       HudMain::getInstance().setVisibility(true);
       HudObjPool::getInstance().setVisibility(true);
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
