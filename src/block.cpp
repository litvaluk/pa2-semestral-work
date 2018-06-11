#include "SDL2/SDL.h"
#include "block.h"

Block::Block(int x, int y, int w, int h, int r, int g, int b) {
  this->x = x;
  this->y = y;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  this->r = r;
  this->g = g;
  this->b = b;
}

void Block::Draw (SDL_Renderer* renderer) {

  SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &rect);
  
}

bool Block::CollidesWith (const Block& block) const {


  if(rect.y + rect.h <= block.rect.y) {
      return false;
  }

  if(rect.y >= block.rect.y + block.rect.h) {
      return false;
  }

  if(rect.x + rect.w <= block.rect.x) {
      return false;
  }

  if(rect.x >= block.rect.x + block.rect.w) {
      return false;
  }

  return true;
}

void Block::SetX (int x) {
  this->x = rect.x = x;
}

void Block::SetY (int y) {
  this->y = rect.y = y;
}

int Block::GetW () const {
  return rect.w;
}

int Block::GetH () const {
  return rect.h;
}

void Block::SetColor (int r, int g, int b) {
  this->r = r;
  this->g = g;
  this->b = b;
}