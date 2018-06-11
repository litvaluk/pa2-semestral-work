#include "SDL2/SDL.h"
#include "block.h"
#include "monster.h"
#include "proximityblock.h"

#include <string>
#include <vector>
#include <iostream>

Monster::Monster (const std::string& name, int str, int def, int vit, int r, int g, int b)
: Block(0, 0, 30, 30, r, g, b){
  this->name = name;
  this->str = str;
  this->def = def;
  this->vit = vit;
  hp = vit*20;
  this->r = r;
  this->g = g;
  this->b = b;
  speed = 2;
  velX = velY = 0;
  direction = rand()%4;
  lastTime = 0;
  randomTime = rand()%1000 + 1000;
}

void Monster::Move (const std::vector<Block>& walls,
                    const std::vector<ProximityBlock>& treasures,
                    const std::vector<Monster>& monsters,
                    ProximityBlock* nextRoomBlock) {

  rect.x += velX;
  x += velX;

  if (nextRoomBlock != NULL && CollidesWith(*nextRoomBlock)) {
    rect.x -= velX;
    x -= velX;
    UpdateDirectionNow ();
  }

  for (auto& wall : walls) {
    if (CollidesWith(wall)) {
      rect.x -= velX;
      x -= velX;
      UpdateDirectionNow ();
      break;
    }
  }

  for (auto& treasure : treasures) {
    if (CollidesWith(treasure)) {
      rect.x -= velX;
      x -= velX;
      UpdateDirectionNow ();
      break;
    }
  }

  for (auto& monster : monsters) {
    if (&monster != this && CollidesWith(monster)) {
      rect.x -= velX;
      x -= velX;
      UpdateDirectionNow ();
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
      UpdateDirectionNow ();
      break;
    }
  }

  for (auto& treasure : treasures) {
    if (CollidesWith(treasure)) {
      rect.y -= velY;
      y -= velY;
      UpdateDirectionNow ();
      break;
    }
  }

  for (auto& monster : monsters) {
    if (&monster != this && CollidesWith(monster)) {
      rect.y -= velY;
      y -= velY;
      UpdateDirectionNow ();
      break;
    }
  }

}

void Monster::UpdateDirection () {
  if (SDL_GetTicks() > lastTime + randomTime) {
    direction = rand()%4;
    velX = velY = 0;
    lastTime = SDL_GetTicks();
    randomTime = rand()%1000 + 1000;
  }
  if (direction == 0) {
    velX = speed;
  }
  if (direction == 1) {
    velX = -speed;
  }
  if (direction == 2) {
    velY = speed;
  }
  if (direction == 3) {
    velY = -speed;
  }
}

void Monster::UpdateDirectionNow () {
  direction = rand()%4;
  velX = velY = 0;
  lastTime = SDL_GetTicks();
  if (direction == 0) {
    velX = speed;
  }
  if (direction == 1) {
    velX = -speed;
  }
  if (direction == 2) {
    velY = speed;
  }
  if (direction == 3) {
    velY = -speed;
  }
}

int Monster::GetLostHp (int playerStr, int playerDef, int playerVit, int playerWeaponStr, int playerArmorDef, int playerHp) {
  int playerHpBeforeFight = playerHp;
  std::cout << "-------------FIGHT--------------" << '\n';
  while (true) {
    int playerDmg = (playerStr+playerDef+playerVit) * (((double)playerStr+playerWeaponStr)/def);
    playerDmg += rand() % (playerDmg/10 + 3);
    std::cout << "Player deals " << playerDmg << " damage." << '\n';
    hp -= playerDmg;
    if (hp <= 0) {
      std::cout << name <<" dies." << '\n';
      return playerHpBeforeFight - playerHp;
    }
    int monsterDmg = (str+def+vit) * ((double)str/(playerDef+playerArmorDef));
    monsterDmg += rand() % (monsterDmg/10 + 3);
    std::cout << name << " deals " << monsterDmg << " damage." << '\n';
    playerHp -= monsterDmg;
    if (playerHp <= 0) {
      std::cout << "Player dies." << '\n';
      return playerHpBeforeFight;
    }
  }
}

int Monster::GetGainedXp () const {
  return str + def + vit;
}

void Monster::SetX (int x){
  this->x = x;
  rect.x = x;
}

void Monster::SetY (int y){
  this->y = y;
  rect.y = y;
}
