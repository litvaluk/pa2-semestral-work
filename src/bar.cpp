#include "SDL2/SDL.h"
#include "bar.h"

Bar::Bar(int x, int y, int w, int h, int r, int g, int b) {
  border.x = x;
  border.y = y;
  border.w = w;
  border.h = h;
  fill.x = bar.x = x + 3;
  fill.y = bar.y = y + 3;
  fill.w = bar.w = maxWidth = w - 2*3;
  fill.h = bar.h = h - 2*3;
  this->r = r;
  this->g = g;
  this->b = b;
}

void Bar::Draw (SDL_Renderer* renderer) {

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &border);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &fill);
  SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &bar);

}

void Bar::Update (int current, int max) {

  bar.w = maxWidth * ((double)current / max);

}
