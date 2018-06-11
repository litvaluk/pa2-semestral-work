#include "SDL2/SDL.h"
#include "block.h"
#include "player.h"
#include "proximityblock.h"

#include <vector>
#include <iostream>

#define SPEED 3

Player::Player (int x, int y, int w, int h, int r, int g, int b)
: Block(x, y, w, h, r, g, b) {
  innerRect.w = 10;
  innerRect.h = 10;
  innerRect.x = rect.x + rect.w/2 - innerRect.w/2;
  innerRect.y = rect.y + rect.h/2 - innerRect.h/2;
  velX = velY = 0;
}

void Player::Move(const std::vector<Block>& walls, const std::vector<ProximityBlock>& treasures, ProximityBlock* nextRoomBlock) {
  rect.x += velX;
  x += velX;

  if (nextRoomBlock != NULL && CollidesWith(*nextRoomBlock)) {
    rect.x -= velX;
    x -= velX;
  }

  for (auto& wall : walls) {
    if (CollidesWith(wall)) {
      rect.x -= velX;
      x -= velX;
      break;
    }
  }

  for (auto& treasure : treasures) {
    if (CollidesWith(treasure)) {
      rect.x -= velX;
      x -= velX;
      break;
    }
  }

  rect.y += velY;
  y += velY;

  if (nextRoomBlock != NULL && CollidesWith(*nextRoomBlock)) {
    rect.y -= velY;
    y -= velY;
  }

  for (auto& wall : walls) {
    if (CollidesWith(wall)) {
      rect.y -= velY;
      y -= velY;
      break;
    }
  }

  for (auto& treasure : treasures) {
    if (CollidesWith(treasure)) {
      rect.y -= velY;
      y -= velY;
      break;
    }
  }

  innerRect.x = rect.x + rect.w/2 - innerRect.w/2;
  innerRect.y = rect.y + rect.h/2 - innerRect.h/2;

}

void Player::HandleEvents(const SDL_Event& event) {

  if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
    switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        velX -= SPEED;
        break;
      case SDLK_RIGHT:
        velX += SPEED;
        break;
      case SDLK_UP:
        velY -= SPEED;
        break;
      case SDLK_DOWN:
        velY += SPEED;
        break;
    }
  }
  if (event.type == SDL_KEYUP && event.key.repeat == 0) {
    switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        velX += SPEED;
        break;
      case SDLK_RIGHT:
        velX -= SPEED;
        break;
      case SDLK_UP:
        velY += SPEED;
        break;
      case SDLK_DOWN:
        velY -= SPEED;
        break;
    }
  }

}

void Player::ResetVelocity () {
    velX = 0;
    velY = 0;
}

void Player::Draw (SDL_Renderer* renderer) {

  SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &rect);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &innerRect);

}
