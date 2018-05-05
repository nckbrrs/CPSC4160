#include <SDL_image.h>
#include <sstream>
#include <string>
#include <algorithm>
#include "hudTip.h"
#include "gameData.h"
#include "ioMod.h"

HudTip& HudTip::getInstance() {
  static HudTip instance;
  return instance;
}

HudTip::HudTip() :
  width(GameData::getInstance().getXmlInt("hudTip/width")),
  height(GameData::getInstance().getXmlInt("hudTip/height")),
  pos(Vector2f(GameData::getInstance().getXmlInt("hudTip/position/x"),
               GameData::getInstance().getXmlInt("hudTip/position/y"))),
  visible(false),
  backgroundColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/backgroundColor/r")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/backgroundColor/g")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/backgroundColor/b")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/backgroundColor/a"))}),
  outlineColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/outlineColor/r")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/outlineColor/g")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/outlineColor/b")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/outlineColor/a"))}),
  textColor({static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/textColor/r")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/textColor/g")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/textColor/b")),
                    static_cast<Uint8>(GameData::getInstance().getXmlInt("hudTip/textColor/a"))})
{ }

void HudTip::draw() {
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
    textToWrite += "                  TIP";
    textToWrite += "\n --------------------------";
    textToWrite += "\n - The road is safe!";

    IoMod::getInstance().writeTextWrapped(textToWrite, pos[0]+5, pos[1]+5, width, textColor);
  }
}
