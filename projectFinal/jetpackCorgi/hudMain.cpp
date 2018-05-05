#include <SDL_image.h>
#include <sstream>
#include <string>
#include <algorithm>
#include "hudMain.h"
#include "gameData.h"
#include "ioMod.h"

HudMain& HudMain::getInstance() {
  static HudMain instance;
  return instance;
}

HudMain::HudMain() :
  width(GameData::getInstance().getXmlInt("hudMain/width")),
  height(GameData::getInstance().getXmlInt("hudMain/height")),
  pos(Vector2f(GameData::getInstance().getXmlInt("hudMain/position/x"),
               GameData::getInstance().getXmlInt("hudMain/position/y"))),
  visible(false),
  backgroundColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/backgroundColor/r")),
                   static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/backgroundColor/g")),
                   static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/backgroundColor/b")),
                   static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/backgroundColor/a"))}),
  outlineColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/outlineColor/r")),
                static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/outlineColor/g")),
                static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/outlineColor/b")),
                static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/outlineColor/a"))}),
  textColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/textColor/r")),
             static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/textColor/g")),
             static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/textColor/b")),
             static_cast<Uint8>(GameData::getInstance().getXmlInt("hudMain/textColor/a"))})
{ }

void HudMain::draw() {
  if (isVisible()) {
    SDL_Rect r;
    r.x = pos[0];
    r.y = pos[1];
    r.w = width;
    r.h = height;

    SDL_Renderer* renderer = IoMod::getInstance().getRenderer();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
    SDL_RenderDrawRect(renderer, &r);

    std::string textToWrite;
    textToWrite += "         CONTROLS";
    textToWrite += "\n ---------------------------";
    textToWrite += "\n - WASD to move";
    textToWrite += "\n - SPACE to bark";
    textToWrite += "\n - F1 to toggle HUDs";
    textToWrite += "\n - M to toggle music";
    textToWrite += "\n - P to pause";
    textToWrite += "\n - R to restart";
    textToWrite += "\n - G to toggle God Mode";

    IoMod::getInstance().writeTextWrapped(textToWrite, pos[0]+5, pos[1]+5, width, textColor);
  }
}
