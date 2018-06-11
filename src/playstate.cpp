#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "gameengine.h"
#include "gamestate.h"
#include "playstate.h"
#include "menustate.h"
#include "infostate.h"
#include "block.h"
#include "player.h"
#include "proximityblock.h"
#include "monster.h"
#include "bar.h"
#include "text.h"
#include "item.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>

extern TTF_Font* coolvetica25;
extern TTF_Font* coolvetica20;

PlayState::PlayState (GameEngine* game, int saveNumber, int str, int def, int vit, int r, int g, int b)
: GameState(game),
hpBar(Bar(1020, 30, 230, 30, 255, 0, 0)),
xpBar(Bar(1020, 660, 230, 30, 161, 58, 244)),
backpackBlock(Block(1010, 439, 10, 10, 255, 0, 0)),
strengthText(Text(1020, 100, "strength: " + std::to_string(str) + " (+0)", {255, 255, 255, 0}, coolvetica25, game->renderer)),
defenseText(Text(1020, 130, "defense: " + std::to_string(def) + " (+0)", {255, 255, 255, 0}, coolvetica25, game->renderer)),
vitalityText(Text(1020, 160, "vitality: " + std::to_string(vit), {255, 255, 255, 0}, coolvetica25, game->renderer)),
hpText(Text(1020, 58, "HP", {255, 255, 255, 0}, coolvetica25, game->renderer)),
xpText(Text(1020, 630, "XP", {255, 255, 255, 0}, coolvetica25, game->renderer)),
lvlText(Text(1020, 605, "LVL", {255, 255, 255, 0}, coolvetica25, game->renderer)),
unspentPointsText(Text(1020, 202, "unspent points: " + std::to_string(0), {255, 255, 255, 0}, coolvetica25, game->renderer)),
equippedText(Text(1020, 260, "Equipped:", {255, 255, 255, 0}, coolvetica25, game->renderer)),
equippedArmorText(Text(1030, 295, "Armor: (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
equippedWeaponText(Text(1030, 320, "Weapon: (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
backpackText(Text(1020, 400, "Backpack: ", {255, 255, 255, 0}, coolvetica25, game->renderer)),
backpackFirstText(Text(1030, 430, "1) (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
backpackSecondText(Text(1030, 455, "2) (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
backpackThirdText(Text(1030, 480, "3) (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
backpackFourthText(Text(1030, 505, "4) (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
backpackFifthText(Text(1030, 530, "5) (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)) {

  for (int i = 0; i < 5; i++) {
    backpack[i] = NULL;
  }

  backpackSelection = false;
  this->saveNumber = saveNumber;
  this->game = game;
  this->str = str;
  this->def = def;
  this->vit = vit;
  this->r = r;
  this->g = g;
  this->b = b;
  weaponStr = armorDef = 0;
  equippedArmor = equippedWeapon = NULL;
  maxHp = 20+20*vit;
  hp = maxHp;
  xp = 0;
  maxXp = 50;
  lvl = 1;
  unspentPoints = 0;
  nextRoomBlock = NULL;
  player = NULL;
  currentRoom = "data/rooms/room1.txt";
  LoadItemList("data/items.txt");
  LoadMonsterList("data/monsters.txt");
  LoadRoom(currentRoom.c_str());
  hpText.UpdateText("HP " + std::to_string(hp) + "/" + std::to_string(maxHp));
  xpText.UpdateText("XP " + std::to_string(xp) + "/" + std::to_string(maxXp));
  lvlText.UpdateText("LVL " + std::to_string(lvl));

  Save();

}

PlayState::PlayState (GameEngine* game, int saveNumber, const std::string& room, int lvl, int str, int def, int vit, int unspentPoints, int hp, int xp, int r, int g, int b, const std::vector<std::string>& items)
: GameState(game),
hpBar(Bar(1020, 30, 230, 30, 255, 0, 0)),
xpBar(Bar(1020, 660, 230, 30, 161, 58, 244)),
backpackBlock(Block(1010, 439, 10, 10, 255, 0, 0)),
strengthText(Text(1020, 100, "strength: " + std::to_string(str) + " (+0)", {255, 255, 255, 0}, coolvetica25, game->renderer)),
defenseText(Text(1020, 130, "defense: " + std::to_string(def) + " (+0)", {255, 255, 255, 0}, coolvetica25, game->renderer)),
vitalityText(Text(1020, 160, "vitality: " + std::to_string(vit), {255, 255, 255, 0}, coolvetica25, game->renderer)),
hpText(Text(1020, 58, "HP", {255, 255, 255, 0}, coolvetica25, game->renderer)),
xpText(Text(1020, 630, "XP", {255, 255, 255, 0}, coolvetica25, game->renderer)),
lvlText(Text(1020, 605, "LVL", {255, 255, 255, 0}, coolvetica25, game->renderer)),
unspentPointsText(Text(1020, 202, "unspent points: " + std::to_string(0), {255, 255, 255, 0}, coolvetica25, game->renderer)),
equippedText(Text(1020, 260, "Equipped:", {255, 255, 255, 0}, coolvetica25, game->renderer)),
equippedArmorText(Text(1030, 295, "Armor: (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
equippedWeaponText(Text(1030, 320, "Weapon: (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
backpackText(Text(1020, 400, "Backpack: ", {255, 255, 255, 0}, coolvetica25, game->renderer)),
backpackFirstText(Text(1030, 430, "1) (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
backpackSecondText(Text(1030, 455, "2) (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
backpackThirdText(Text(1030, 480, "3) (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
backpackFourthText(Text(1030, 505, "4) (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)),
backpackFifthText(Text(1030, 530, "5) (empty)", {255, 255, 255, 0}, coolvetica20, game->renderer)) {

  nextRoomBlock = NULL;
  player = NULL;
  currentRoom = room;

  backpackSelection = false;
  this->saveNumber = saveNumber;
  this->game = game;
  this->lvl = lvl;
  this->str = str;
  this->def = def;
  this->vit = vit;
  this->r = r;
  this->g = g;
  this->b = b;
  this->unspentPoints = unspentPoints;
  this->hp = hp;
  this->xp = xp;

  LoadItemList("data/items.txt");
  LoadMonsterList("data/monsters.txt");
  LoadRoom(currentRoom.c_str());

  maxHp = 20+20*vit;
  maxXp = 50 * pow(1.5, lvl-1);

  equippedArmor = GetItem(items[0]);
  equippedWeapon = GetItem(items[1]);
  if (equippedArmor != NULL) {
    armorDef = equippedArmor->GetStat();
    defenseText.UpdateText("defense: " + std::to_string(def) + " (+" + std::to_string(armorDef) + ")");
    equippedArmorText.UpdateText("Armor: " + equippedArmor->GetName());
  }
  else {
    armorDef = 0;
  }
  if (equippedWeapon != NULL) {
    weaponStr = equippedWeapon->GetStat();
    strengthText.UpdateText("strength: " + std::to_string(str) + " (+" + std::to_string(weaponStr) + ")");
    equippedWeaponText.UpdateText("Weapon: " + equippedWeapon->GetName());
  }
  else {
    weaponStr = 0;
  }

  hpText.UpdateText("HP " + std::to_string(hp) + "/" + std::to_string(maxHp));
  xpText.UpdateText("XP " + std::to_string(xp) + "/" + std::to_string(maxXp));
  lvlText.UpdateText("LVL " + std::to_string(lvl));

  for (int i = 2; i < 7; i++) {
    backpack[i-2] = GetItem(items[i]);
  }

  UpdateBackpackText();

}

PlayState::~PlayState () {

    delete player;
    if (nextRoomBlock != NULL) {
      delete nextRoomBlock;
    }

    for(auto& item : itemList) {
      delete item;
    }

    for(int i = 0; i < 5; i++) {
      if (backpack[i] != NULL) {
        delete backpack[i];
      }
    }

    if (equippedArmor != NULL) {
      delete equippedArmor;
    }

    if (equippedWeapon != NULL) {
      delete equippedWeapon;
    }
}

void PlayState::HandleEvents (GameEngine* game) {

  SDL_Event event;

	while (SDL_PollEvent(&event)) {

    if (backpackSelection) {
      HandleBackpackEvents(event);
    }
    else {
      player->HandleEvents(event);
    }

    if (event.type == SDL_QUIT && event.key.repeat == 0) {
      game->Quit();
    }

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          if (backpackSelection) {
            backpackSelection = false;
            player->ResetVelocity();
          }
          else {
            game->SetState(new MenuState(game));
          }
          break;
        case SDLK_SPACE:
          if (!backpackSelection) {
            if (nextRoomBlock != NULL && nextRoomBlock->ProximityCheck(*player)) {
              SwitchRoom(nextRoom.c_str());
              if (player == NULL) {
                game->SetState(new InfoState(game, "Player position not loaded!"));
                return;
              }
            }
            for (size_t i = 0; i < treasures.size(); i++) {
              if (treasures[i].ProximityCheck(*player)) {
                PushItemToBackpack(itemList[rand()%itemList.size()]);
                treasures.erase(treasures.begin() + i);
                i--;
                UpdateBackpackText();
              }
            }
          }
          break;
        case SDLK_s:
          if (unspentPoints > 0) {
            str++;
            strengthText.UpdateText("strength: " + std::to_string(str) + " (+" + std::to_string(weaponStr) + ")");
            unspentPoints--;
            unspentPointsText.UpdateText("unspent points: " + std::to_string(unspentPoints));
          }
          break;
        case SDLK_d:
          if (unspentPoints > 0) {
            def++;
            defenseText.UpdateText("defense: " + std::to_string(def) + " (+" + std::to_string(armorDef) + ")");
            unspentPoints--;
            unspentPointsText.UpdateText("unspent points: " + std::to_string(unspentPoints));
          }
          break;
        case SDLK_v:
          if (unspentPoints > 0) {
            vit++;
            vitalityText.UpdateText("vitality: " + std::to_string(vit));
            maxHp += 20;
            hp += 20;
            hpText.UpdateText("HP " + std::to_string(hp) + "/" + std::to_string(maxHp));
            unspentPoints--;
            unspentPointsText.UpdateText("unspent points: " + std::to_string(unspentPoints));
          }
          break;
        case SDLK_b:
          player->ResetVelocity();
          if (backpackSelection) {
            backpackSelection = false;
          }
          else {
            backpackSelection = true;
            itemSelected = 0;
            backpackBlock.SetY(439);
          }
          break;
        case SDLK_1:
          if (backpack[0] != NULL) {
            UseItem(0);
          }
          break;
        case SDLK_2:
          if (backpack[1] != NULL) {
            UseItem(1);
          }
          break;
        case SDLK_3:
          if (backpack[2] != NULL) {
            UseItem(2);
          }
          break;
        case SDLK_4:
          if (backpack[3] != NULL) {
            UseItem(3);
          }
          break;
        case SDLK_5:
          if (backpack[4] != NULL) {
            UseItem(4);
          }
          break;
        }
    }
  }
}

void PlayState::Update (GameEngine* game) {

  if (player == NULL) {
    game->SetState(new InfoState(game, "Player position not found!"));
    return;
  }

  if (xp >= maxXp) {
    LevelUp();
  }

  hpBar.Update(hp, maxHp);
  xpBar.Update(xp, maxXp);

  player->Move(walls, treasures, nextRoomBlock);

  for (auto& treasure : treasures) {
    treasure.ProximityCheck(*player);
  }

  if (nextRoomBlock != NULL) {
    nextRoomBlock->ProximityCheck(*player);
  }

  for (auto& monster : monsters) {
    monster.UpdateDirection();
    monster.Move(walls, treasures, monsters, nextRoomBlock);
  }

  for (size_t i = 0; i < monsters.size(); i++) {
    if (player->CollidesWith(monsters[i])) {
      hp -= monsters[i].GetLostHp(str, def, vit, weaponStr, armorDef, hp);
      xp += monsters[i].GetGainedXp();
      hpText.UpdateText("HP " + std::to_string(hp) + "/" + std::to_string(maxHp));
      xpText.UpdateText("XP " + std::to_string(xp) + "/" + std::to_string(maxXp));
      monsters.erase(monsters.begin() + i);
    }
  }

  if (hp <= 0) {
    game->SetState(new InfoState(game, "You are dead!"));
  }

}

void PlayState::Draw (GameEngine* game) {

  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game->renderer);

  for (auto& wall : walls) {
    wall.Draw(game->renderer);
  }

  for (auto& treasure : treasures) {
    treasure.Draw(game->renderer);
  }

  for (auto& monster : monsters) {
    monster.Draw(game->renderer);
  }

  if (player != NULL) {
    player->Draw(game->renderer);
  }

  if (nextRoomBlock != NULL) {
    nextRoomBlock->Draw(game->renderer);
  }

  DrawUI();

  SDL_RenderPresent(game->renderer);

}

void PlayState::LoadRoom(const char* src) {

  currentRoom = src;

  std::ifstream ifs(src, std::ios_base::in);
  ifs.unsetf(std::ios_base::skipws);

  if (nextRoomBlock != NULL) {
    delete nextRoomBlock;
  }
  if (player != NULL) {
    delete player;
  }
  nextRoomBlock = NULL;
  player = NULL;

  char tmp;
  int x = 30;
  int y = 30;

  while (true) {
    ifs >> tmp;
    if (ifs.eof()) break;
    if (tmp == '#') {
      walls.push_back(Block(x, y, 30, 30, 200, 200, 200));
    }
    if (tmp == 'P' && player == NULL) {
      player = new Player(x, y, 30, 30, r, g, b);
    }
    if (tmp == 'N' && nextRoomBlock == NULL) {
      nextRoomBlock = new ProximityBlock(x, y, 30, 30, 120, 120, 120, 80, 80, 80);
    }
    if (tmp == 'T') {
      treasures.push_back(ProximityBlock(x, y, 30, 30, 255, 255, 0, 180, 180, 0));
    }
    if (tmp == 'M') {
      monsters.push_back(monsterList[rand()%monsterList.size()]);
      monsters.back().SetX(x);
      monsters.back().SetY(y);
    }
    if (tmp == 'B') {
      monsters.push_back(Monster("Final boss", 10, 10, 10, 244, 66, 194));
      monsters.back().SetX(x);
      monsters.back().SetY(y);
    }
    if (tmp == ':') {
      nextRoom.clear();
      nextRoom += "data/rooms/";
      while (true) {
        ifs >> tmp;
        if (ifs.eof()) {
          break;
        }
        nextRoom += tmp;
      }
      nextRoom += ".txt";
      break;
    }
    if (tmp == '\n') {
      x = 30;
      y += 30;
      continue;
    }
    x += 30;
  }

}

void PlayState::LoadItemList(const char* src) {

  std::ifstream ifs(src, std::ios_base::in);
  ifs.unsetf(std::ios_base::skipws);

  char type;
  std::string name;
  int itemAttr;

  char tmpChar = '0';
  int state = 0;

  while (true) {

    switch (state) {
      case 0:
        ifs >> type;
        ifs >> tmpChar;
        state = 1;
        break;
      case 1:
        ifs >> tmpChar;
        if (tmpChar == ':') {
          state = 2;
          break;
        }
        name += tmpChar;
        break;
      case 2:
      ifs >> itemAttr;
      ifs >> tmpChar;
      state = 0;
      if (type == 'a' || type == 'w' || type == 'p') {
        itemList.push_back(new Item(name, itemAttr, type));
      }
      name.clear();
      break;
    }

    if (ifs.eof()) {
      break;
    }
  }

}

void PlayState::LoadMonsterList (const char *src) {

  std::ifstream ifs(src, std::ios_base::in);
  ifs.unsetf(std::ios_base::skipws);

  std::string name;
  int str, def, vit, r, g, b;

  char tmpChar = '0';
  int state = 0;

  while (true) {

    switch (state) {
      case 0:
        ifs >> tmpChar;
        if (tmpChar == ':') {
          state = 1;
          break;
        }
        name += tmpChar;
        break;
      case 1:
        ifs >> str;
        ifs >> tmpChar;
        state = 2;
        break;
      case 2:
        ifs >> def;
        ifs >> tmpChar;
        state = 3;
        break;
      case 3:
        ifs >> vit;
        ifs >> tmpChar;
        state = 4;
        break;
      case 4:
        ifs >> r;
        ifs >> tmpChar;
        state = 5;
        break;
      case 5:
        ifs >> g;
        ifs >> tmpChar;
        state = 6;
        break;
      case 6:
        ifs >> b;
        state = 0;
        ifs >> tmpChar;
        monsterList.push_back(Monster(name, str, def, vit, r, g, b));
        name.clear();
        break;
    }

    if (ifs.eof()) {
      break;
    }
  }

}

void PlayState::SwitchRoom (const char* target) {

  std::ifstream ifs(target, std::ios_base::in);
  if (!ifs.is_open()) {
    game->SetState(new InfoState(game, "Next room doesn't exist"));
    return;
  }

  monsters.clear();
  treasures.clear();
  walls.clear();
  LoadRoom(target);
  Save();
}

void PlayState::LevelUp() {
  xp = xp%maxXp;
  maxXp *= 1.5;
  lvl++;
  unspentPoints++;
  xpText.UpdateText("XP " + std::to_string(xp) + "/" + std::to_string(maxXp));
  unspentPointsText.UpdateText("unspent points: " + std::to_string(unspentPoints));
  lvlText.UpdateText("LVL " + std::to_string(lvl));
}

Item* PlayState::GetItemFromBackpack (int x) {
  Item* item = backpack[x];
  backpack[x] = NULL;
  return item;
}

bool PlayState::PushItemToBackpack (Item* item) {
  for (int i = 0; i < 5; i++) {
    if (backpack[i] == NULL) {
      backpack[i] = new Item(*item);
      return true;
    }
  }
  return false;
}

bool PlayState::DestroyItemFromBackpack (int x) {
  if (backpack[x] != NULL) {
    delete backpack[x];
    backpack[x] = NULL;
    return true;
  }
  return false;
}

void PlayState::UseItem (int x) {

  Item* tmp = NULL;
  switch (backpack[x]->GetType()) {
    case 'w':
      if (equippedWeapon != NULL) {
        tmp = equippedWeapon;
      }
      weaponStr = backpack[x]->GetStat();
      equippedWeapon = new Item(*backpack[x]);
      strengthText.UpdateText("strength: " + std::to_string(str) + " (+" + std::to_string(weaponStr) + ")");
      equippedWeaponText.UpdateText("Weapon: " + equippedWeapon->GetName());
      DestroyItemFromBackpack(x);
      if (tmp != NULL) {
        PushItemToBackpack(tmp);
        delete tmp;
      }
      break;
    case 'a':
      if (equippedArmor != NULL) {
        tmp = equippedArmor;
      }
      armorDef = backpack[x]->GetStat();
      equippedArmor = new Item(*backpack[x]);
      defenseText.UpdateText("defense: " + std::to_string(def) + " (+" + std::to_string(armorDef) + ")");
      equippedArmorText.UpdateText("Armor: " + equippedArmor->GetName());
      DestroyItemFromBackpack(x);
      if (tmp != NULL) {
        PushItemToBackpack(tmp);
        delete tmp;
      }
      break;
    case 'p':
      hp += maxHp * 0.01 * backpack[x]->GetStat();
      if (hp > maxHp) {
        hp = maxHp;
      }
      hpText.UpdateText("HP " + std::to_string(hp) + "/" + std::to_string(maxHp));
      DestroyItemFromBackpack(x);
      break;
  }

  UpdateBackpackText();

}

void PlayState::DrawUI () {

  hpBar.Draw(game->renderer);
  xpBar.Draw(game->renderer);
  strengthText.Draw(game->renderer);
  defenseText.Draw(game->renderer);
  vitalityText.Draw(game->renderer);
  hpText.Draw(game->renderer);
  xpText.Draw(game->renderer);
  lvlText.Draw(game->renderer);
  unspentPointsText.Draw(game->renderer);
  equippedText.Draw(game->renderer);
  equippedWeaponText.Draw(game->renderer);
  equippedArmorText.Draw(game->renderer);
  backpackText.Draw(game->renderer);
  backpackFirstText.Draw(game->renderer);
  backpackSecondText.Draw(game->renderer);
  backpackThirdText.Draw(game->renderer);
  backpackFourthText.Draw(game->renderer);
  backpackFifthText.Draw(game->renderer);

  if (backpackSelection) {
    backpackBlock.Draw(game->renderer);
  }

}

void PlayState::UpdateBackpackText () {
  if (backpack[0] == NULL) {
    backpackFirstText.UpdateText("1) (empty)");
  }
  else {
    backpackFirstText.UpdateText("1) " + backpack[0]->GetName());
  }
  if (backpack[1] == NULL) {
    backpackSecondText.UpdateText("2) (empty)");
  }
  else {
    backpackSecondText.UpdateText("2) " + backpack[1]->GetName());
  }
  if (backpack[2] == NULL) {
    backpackThirdText.UpdateText("3) (empty)");
  }
  else {
    backpackThirdText.UpdateText("3) " + backpack[2]->GetName());
  }
  if (backpack[3] == NULL) {
    backpackFourthText.UpdateText("4) (empty)");
  }
  else {
    backpackFourthText.UpdateText("4) " + backpack[3]->GetName());
  }
  if (backpack[4] == NULL) {
    backpackFifthText.UpdateText("5) (empty)");
  }
  else {
    backpackFifthText.UpdateText("5) " + backpack[4]->GetName());
  }
}

void PlayState::HandleBackpackEvents (SDL_Event& event) {

  int shift = 25;

  if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
    switch (event.key.keysym.sym) {
      case SDLK_UP:
        if (itemSelected == 0) {
          itemSelected = 4;
          backpackBlock.SetY(539);
        }
        else {
          itemSelected--;
          backpackBlock.SetY(backpackBlock.GetY() - shift);
        }
        break;
      case SDLK_DOWN:
        if (itemSelected == 4) {
          itemSelected = 0;
          backpackBlock.SetY(439);
        }
        else {
          itemSelected++;
          backpackBlock.SetY(backpackBlock.GetY() + shift);
        }
        break;
      case SDLK_SPACE:
        if (backpack[itemSelected] != NULL) {
          UseItem(itemSelected);
        }
        break;
      case SDLK_BACKSPACE:
        if (backpack[itemSelected] != NULL) {
          DestroyItemFromBackpack(itemSelected);
          UpdateBackpackText();
        }
        break;
      case SDLK_DELETE:
        if (backpack[itemSelected] != NULL) {
          DestroyItemFromBackpack(itemSelected);
          UpdateBackpackText();
        }
        break;
    }
  }

}

Item* PlayState::GetItem (const std::string& name) const {
  for (auto item : itemList) {
    if (item->GetName() == name) {
      return new Item(*item);
    }
  }
  return NULL;
}

void PlayState::Save () {

  std::string oldName = "data/saves/save" + std::to_string(saveNumber+1) + ".txt";
  remove(oldName.c_str());
  std::ofstream ofs("data/saves/save" + std::to_string(saveNumber+1) + ".txt", std::ios::out);
  if (ofs.is_open()) {
    std::time_t date = std::time(NULL);
    std::tm localdate = *std::localtime(&date);
    char buffer[50];
    strftime(buffer, 50, "%y/%m/%d - %H:%M:%S", &localdate);
    ofs << buffer << "\n";
    ofs << currentRoom << '\n';
    ofs << lvl << '\n';
    ofs << str << '\n';
    ofs << def << '\n';
    ofs << vit << '\n';
    ofs << unspentPoints << '\n';
    ofs << hp << '\n';
    ofs << xp << '\n';
    ofs << r << '\n';
    ofs << g << '\n';
    ofs << b << '\n';
    if (equippedArmor != NULL) {
      ofs << equippedArmor->GetName() << '\n';
    }
    else {
      ofs << "-" << '\n';
    }
    if (equippedWeapon != NULL) {
      ofs << equippedWeapon->GetName() << '\n';
    }
    else {
      ofs << "-" << '\n';
    }
    for (int i = 0; i < 5; i++) {
      if (backpack[i] != NULL) {
        ofs << backpack[i]->GetName() << "\n";
      }
      else {
        ofs << "-" << '\n';
      }
    }
    ofs.close();
  }

}