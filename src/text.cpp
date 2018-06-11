#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "graphicalobject.h"
#include "text.h"

#include <string>
#include <iostream>

Text::Text(int x, int y, std::string text, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer) {

  this->color = color;
  this->font = font;
  this->renderer = renderer;
  this->x = rect.x = x;
  this->y = rect.y = y;
  texture = NULL;
  UpdateText(text);

}

Text::~Text() {

  Free();

}

void Text::Draw (SDL_Renderer* renderer) {

  SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);

}

void Text::UpdateText (std::string text) {

  Free();
  SDL_Surface* textureSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
  texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
  rect.w = textureSurface->w;
  rect.h = textureSurface->h;
  SDL_FreeSurface(textureSurface);

}

void Text::Free () {

  if( texture != NULL ) {
    SDL_DestroyTexture( texture );
    texture = NULL;
    rect.w = 0;
    rect.h = 0;
  }

}
