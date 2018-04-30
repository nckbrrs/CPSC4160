#include <iostream>
#include "background.h"
#include "renderContext.h"

Background::Background(const std::string& name, int fact) :
  image(RenderContext::getInstance()->getImage(name)),
  factor(fact),
    backgroundWidth( GameData::getInstance().getXmlInt("background/width") ),
    imageWidth( image->getWidth() ),
    viewX(0.0), viewY(0.0),
    view(Viewport::getInstance())
{ }

void Background::update() {
  viewX = static_cast<int>(view.getPositionX() / factor) % imageWidth;
  viewY = view.getPositionY();
}

void Background::draw() const {
  image->draw(0,0,-viewX,-viewY);
  image->draw(0,0,imageWidth-viewX,-viewY);
}
