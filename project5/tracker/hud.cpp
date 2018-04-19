#include <SDL_image.h>
#include <sstream>
#include <string>
#include <algorithm>
#include "hud.h"
#include "gameData.h"
#include "ioMod.h"

Hud& Hud::getInstance() {
  static Hud instance;
  return instance;
}

Hud::Hud() :
  width(GameData::getInstance().getXmlInt("HUD/width")),
  height(GameData::getInstance().getXmlInt("HUD/height")),
  pos(Vector2f(GameData::getInstance().getXmlInt("HUD/position/x"),
               GameData::getInstance().getXmlInt("HUD/position/y"))),
  visible(true),
  backgroundColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/backgroundColor/r")),
                   static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/backgroundColor/g")),
                   static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/backgroundColor/b")),
                   static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/backgroundColor/a"))}),
  outlineColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/outlineColor/r")),
                static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/outlineColor/g")),
                static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/outlineColor/b")),
                static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/outlineColor/a"))}),
  textColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/textColor/r")),
             static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/textColor/g")),
             static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/textColor/b")),
             static_cast<Uint8>(GameData::getInstance().getXmlInt("HUD/textColor/a"))})
{ }

void Hud::draw(int activeProj, int freeProj) {
  if (isVisible()) {
    SDL_Rect r;
    r.x = getPosition()[0];
    r.y = getPosition()[1];
    r.w = getWidth();
    r.h = getHeight();

    SDL_Renderer* renderer = IoMod::getInstance().getRenderer();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
    SDL_RenderDrawRect(renderer, &r);

    std::string textToWrite;
    textToWrite += " - WASD to move\n - SPACE to shoot";
    textToWrite += "\n - active WOOFs: " + std::to_string(activeProj);
    textToWrite += "\n - free WOOFs: " + std::to_string(freeProj);
    textToWrite += "\n\n - F1 to toggle this HUD";

    IoMod::getInstance().writeTextWrapped(textToWrite,
                          getPosition()[0]+2,
                          getPosition()[1]+2,
                          getWidth(),
                          getTextColor());
  }
}
