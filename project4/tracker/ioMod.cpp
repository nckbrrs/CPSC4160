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
  SDL_Surface* surface =
    TTF_RenderText_Solid(defaultFont, msg.c_str(), textColor);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void IoMod::writeText(const std::string& msg, int x, int y, SDL_Color customColor) const {
  SDL_Surface* surface =
    TTF_RenderText_Solid(defaultFont, msg.c_str(), customColor);

      std::cout << "surface created" << std::endl;
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  std::cout << "texture created" << std::endl;
  int textWidth = surface->w;
  int textHeight = surface->h;
  std::cout << "text width and height initialized" << std::endl;

  SDL_FreeSurface(surface);
  std::cout << "surface freed" << std::endl;

  SDL_Rect dst = {x, y, textWidth, textHeight};
  std::cout << "dst initialized" << std::endl;


  SDL_RenderCopy(renderer, texture, NULL, &dst);
  std::cout << "render copied" << std::endl;

  SDL_DestroyTexture(texture);
  std::cout << "texture destroyed" << std::endl;

}

void IoMod::writeText(const std::string& msg, int x, int y, TTF_Font* customFont) const {
  SDL_Surface* surface =
    TTF_RenderText_Solid(customFont, msg.c_str(), textColor);

  std::cout << "surface created" << std::endl;

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  std::cout << "texture created" << std::endl;

  int textWidth = surface->w;
  int textHeight = surface->h;

  std::cout << "text width and height initialized" << std::endl;
  SDL_FreeSurface(surface);
  std::cout << "surface freed" << std::endl;
  SDL_Rect dst = {x, y, textWidth, textHeight};
  std::cout << "dst initialized" << std::endl;

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  std::cout << "render copied" << std::endl;
  SDL_DestroyTexture(texture);
  std::cout << "texture destroyed" << std::endl;
}
