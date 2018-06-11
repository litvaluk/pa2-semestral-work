#include "SDL2/SDL.h"
#include "block.h"
#include "proximityblock.h"

#include <cmath>
#include <iostream>

ProximityBlock::ProximityBlock (int x, int y, int w, int h, int rNot, int gNot, int bNot, int rProx, int gProx, int bProx)
: Block(x, y, w, h, rNot, gNot, bNot) {

  this->rNot = rNot;
  this->gNot = gNot;
  this->bNot = bNot;
  this->rProx = rProx;
  this->gProx = gProx;
  this->bProx = bProx;

}

bool ProximityBlock::ProximityCheck (const Block& block) {

  double xDiff = rect.x + rect.w / 2 - block.rect.x - block.rect.w / 2;
  double yDiff = rect.y + rect.h / 2 - block.rect.y - block.rect.h / 2;
  double current = sqrt(xDiff*xDiff + yDiff*yDiff);
  double target = 45;

  if (current <= target) {
    SetColor(rProx, gProx, bProx);
    return true;
  }

  else {
    SetColor(rNot, gNot, bNot);
    return false;
  }

}

void ProximityBlock::SetColor (int r, int g, int b) {
  this->r = r;
  this->g = g;
  this->b = b;
}
