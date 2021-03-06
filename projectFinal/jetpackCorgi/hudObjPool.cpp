#include <SDL_image.h>
#include <sstream>
#include <string>
#include <algorithm>
#include "hudObjPool.h"
#include "gameData.h"
#include "ioMod.h"

HudObjPool& HudObjPool::getInstance() {
  static HudObjPool instance;
  return instance;
}

HudObjPool::HudObjPool() :
  width(GameData::getInstance().getXmlInt("hudObjPool/width")),
  height(GameData::getInstance().getXmlInt("hudObjPool/height")),
  pos(Vector2f(GameData::getInstance().getXmlInt("hudObjPool/position/x"),
               GameData::getInstance().getXmlInt("hudObjPool/position/y"))),
  visible(false),
  backgroundColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/backgroundColor/r")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/backgroundColor/g")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/backgroundColor/b")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/backgroundColor/a"))}),
  outlineColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/outlineColor/r")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/outlineColor/g")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/outlineColor/b")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/outlineColor/a"))}),
  textColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/textColor/r")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/textColor/g")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/textColor/b")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudObjPool/textColor/a"))})
{ }

void HudObjPool::draw(int activeProj, int freeProj) {
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
    textToWrite += "        OBJECT POOL";
    textToWrite += "\n --------------------------";
    textToWrite += "\n - Active WOOFs: " + std::to_string(activeProj);
    textToWrite += "\n - Free WOOFs: " + std::to_string(freeProj);

    IoMod::getInstance().writeTextWrapped(textToWrite, pos[0]+5, pos[1]+5, width, textColor);
  }
}
