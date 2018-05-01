#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class IoMod {
public:
  static IoMod& getInstance();
  ~IoMod();
  SDL_Texture* readTexture(const std::string& filename);
  SDL_Surface* readSurface(const std::string& filename);
  void writeText(const std::string&, int, int) const;
  void writeText(const std::string&, int, int, SDL_Color) const;
  void writeTextWrapped(const std::string&, int, int, int) const;
  void writeTextWrapped(const std::string&, int, int, int, SDL_Color) const;
  SDL_Renderer* getRenderer() const { return renderer; }

private:
  int init;
  SDL_Renderer* renderer;
  TTF_Font* defaultFont;
  SDL_Color textColor;
  IoMod();
  IoMod(const IoMod&);
  IoMod& operator=(const IoMod&);
};