#include "renderContext.h"
#include "gameData.h"

RenderContext::RenderContext() :
  window(nullptr),
  renderer(nullptr)
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
	  throw (std::string("Could not init SDL: ") + SDL_GetError());
 	}
  window = initWindow();
  renderer = initRenderer();
}

RenderContext::~RenderContext() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow( window );
  SDL_Quit();
}

RenderContext* RenderContext::getInstance() {
  if (instance) return instance;
  instance = new RenderContext;
  return instance;
}

SDL_Window* RenderContext::initWindow( ) {
  std::string title = GameData::getInstance().getXmlStr("title");
  int width = GameData::getInstance().getXmlInt("view/width");
  int height = GameData::getInstance().getXmlInt("view/height");
	window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED,
             SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );
  if( window == NULL ) {
    throw (std::string("Couldn't make a window: ")+SDL_GetError());
  }
  return window;
}

SDL_Renderer* RenderContext::initRenderer() {
  SDL_Renderer* renderer =
    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if ( renderer == NULL ) throw std::string("No Renderer");
  return renderer;
}
