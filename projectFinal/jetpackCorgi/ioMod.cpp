#include <SDL_image.h>
#include "ioMod.h"
#include "gameData.h"
#include "renderContext.h"

IoMod& IoMod::getInstance() {
  static IoMod instance;
  return instance;
}

IoMod::~IoMod() {
  TTF_CloseFont(defaultFont);
  TTF_Quit();
}

IoMod::IoMod() :
  init(TTF_Init()),
  renderer( RenderContext::getInstance()->getRenderer() ),
  defaultFont(TTF_OpenFont(GameData::getInstance().getXmlStr("defaultFont/file").c_str(),
                          GameData::getInstance().getXmlInt("defaultFont/size"))),
  textColor({0xff, 0, 0, 0})
{
  if ( init == -1 ) {
    throw std::string("error: Couldn't init default font");
  }
  if (defaultFont == NULL) {
    throw std::string("error: font not found");
  }
  textColor.r = GameData::getInstance().getXmlInt("defaultFont/red");
  textColor.g = GameData::getInstance().getXmlInt("defaultFont/green");
  textColor.b = GameData::getInstance().getXmlInt("defaultFont/blue");
  textColor.a = GameData::getInstance().getXmlInt("defaultFont/alpha");
}

SDL_Texture* IoMod::readTexture(const std::string& filename) {
  SDL_Texture *texture = IMG_LoadTexture(renderer, filename.c_str());
  if ( texture == NULL ) {
    throw std::string("Couldn't load texture: ") + filename;
  }
  return texture;
}

SDL_Surface* IoMod::readSurface(const std::string& filename) {
  SDL_Surface *surface = IMG_Load(filename.c_str());
  if ( !surface ) {
    throw std::string("Couldn't load surface: ") + filename;
  }
  return surface;
}

void IoMod::writeText(const std::string& msg, int x, int y) const {
  SDL_Surface* surface = TTF_RenderText_Blended(defaultFont, msg.c_str(), textColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeText(const std::string& msg, int x, int y, SDL_Color customColor) const {
  SDL_Surface* surface = TTF_RenderText_Blended(defaultFont, msg.c_str(), customColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextBold(const std::string& msg, int x, int y) const {
  TTF_SetFontStyle(defaultFont, TTF_STYLE_BOLD);
  SDL_Surface* surface = TTF_RenderText_Blended(defaultFont, msg.c_str(), textColor);
  TTF_SetFontStyle(defaultFont, TTF_STYLE_NORMAL);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextBold(const std::string& msg, int x, int y, SDL_Color customColor) const {
  TTF_SetFontStyle(defaultFont, TTF_STYLE_BOLD);
  SDL_Surface* surface = TTF_RenderText_Blended(defaultFont, msg.c_str(), customColor);
  TTF_SetFontStyle(defaultFont, TTF_STYLE_NORMAL);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextWrapped(const std::string& msg, int x, int y, int wrapWidth) const {
  SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(defaultFont, msg.c_str(), textColor, wrapWidth);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextWrapped(const std::string& msg, int x, int y, int wrapWidth, SDL_Color customColor) const {
  SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(defaultFont, msg.c_str(), customColor, wrapWidth);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextWrappedBold(const std::string& msg, int x, int y, int wrapWidth) const {
  TTF_SetFontStyle(defaultFont, TTF_STYLE_BOLD);
  SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(defaultFont, msg.c_str(), textColor, wrapWidth);
  TTF_SetFontStyle(defaultFont, TTF_STYLE_NORMAL);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeTextWrappedBold(const std::string& msg, int x, int y, int wrapWidth, SDL_Color customColor) const {
  TTF_SetFontStyle(defaultFont, TTF_STYLE_BOLD);
  SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(defaultFont, msg.c_str(), customColor, wrapWidth);
  TTF_SetFontStyle(defaultFont, TTF_STYLE_NORMAL);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  int textWidth = surface->w;
  int textHeight = surface->h;

  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};
  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}
