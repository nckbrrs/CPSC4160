#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "multiSprite.h"

class TwoWayMultiSprite : public MultiSprite {
public:
  TwoWayMultiSprite(const std::string&);
  TwoWayMultiSprite(const TwoWayMultiSprite&);
  virtual ~TwoWayMultiSprite() { }

protected:
  unsigned numLeftFrames;
  unsigned numRightFrames;

  virtual void advanceFrame(Uint32 ticks) override;
  TwoWayMultiSprite& operator=(const TwoWayMultiSprite&);
};
#endif
