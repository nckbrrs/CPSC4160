#include <string>
#include "image.h"
#include "viewport.h"

class Background {
public:
  Background(const std::string& name, int fact);
  void update();
  void draw() const;

private:
  Image* const image;
  int factor;
  unsigned backgroundWidth;
  unsigned imageWidth;
  float viewX;
  float viewY;
  const Viewport & view;
  Background(const Background&);
  Background& operator=(const Background&);
};
