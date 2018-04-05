#ifndef SMARTDRAWABLE__H
#define SMARTDRAWABLE__H
#include <string>
#include "vector2f.h"
#include "gameData.h"
#include "player.h"

class SmartDrawable {
public:
  SmartDrawable(const std::string& name, const Player* p) :
    currentMode(NORMAL),
    playerPos(p->getPosition()),
    playerWidth(p->getScaledWidth()),
    playerHeight(p->getScaledHeight()),
    safeDistance(GameData::getInstance().getXmlFloat(name+"/safeDistance"))
 { }

 SmartDrawable(const SmartDrawable& s) :
   currentMode(s.currentMode),
   playerPos(s.playerPos),
   playerWidth(s.playerWidth),
   playerHeight(s.playerHeight),
   safeDistance(s.safeDistance)
 { }

 virtual ~SmartDrawable() { }

 enum MODE {NORMAL, EVADE};

 virtual void moveLeft() = 0;
 virtual void moveRight() = 0;
 virtual void moveUp() = 0;
 virtual void moveDown() = 0;

 virtual const Vector2f& getPlayerPos() const  { return playerPos; }
 virtual void  setPlayerPos(const Vector2f& p) { playerPos = p; }

 virtual int  getPlayerWidth() const { return playerWidth; }
 virtual void setPlayerWidth(int w) { playerWidth = w; }

 virtual int  getPlayerHeight() const { return playerHeight; }
 virtual void setPlayerHeight(int h) { playerHeight = h; }

 virtual float getSafeDistance() const { return safeDistance; }
 virtual void  setSafeDistance(float d) { safeDistance = d; }

 virtual MODE getCurrentMode() const { return currentMode; }
 virtual void setCurrentMode(MODE m) { currentMode = m; }

private:
  MODE currentMode;
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  float safeDistance;
};
#endif
