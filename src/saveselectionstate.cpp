#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "text.h"
#include "block.h"
#include "saveselectionstate.h"
#include "playstate.h"
#include "creationstate.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BLOCK_WIDTH_OFFSET 20
#define BLOCK_HEIGHT_OFFSET 2

extern TTF_Font* coolvetica40;
extern TTF_Font* coolvetica35;

SaveSelectionState::SaveSelectionState (GameEngine* game)
: GameState(game),
selectsave(Text(0, 35, "Select save", {255, 255, 255, 0}, coolvetica40, game->renderer)),
save1(Text(0, 250, "(empty)", {255, 255, 255, 0}, coolvetica35, game->renderer)),
save2(Text(0, 320, "(empty)", {255, 255, 255, 0}, coolvetica35, game->renderer)),
save3(Text(0, 390, "(empty)", {255, 255, 255, 0}, coolvetica35, game->renderer)),
save4(Text(0, 460, "(empty)", {255, 255, 255, 0}, coolvetica35, game->renderer)),
save5(Text(0, 530, "(empty)", {255, 255, 255, 0}, coolvetica35, game->renderer)),
left(Block(10, 10, 20, 20, 255, 0, 0)),
right(Block(10, 10, 20, 20, 255, 0, 0)) {

  save1loaded = save2loaded = save3loaded = save4loaded = save5loaded = false;

  UpdateSaveNames();

  selectsave.SetX(SCREEN_WIDTH/2 - selectsave.GetW()/2);
  save1.SetX(SCREEN_WIDTH/2 - save1.GetW()/2);
  save2.SetX(SCREEN_WIDTH/2 - save2.GetW()/2);
  save3.SetX(SCREEN_WIDTH/2 - save3.GetW()/2);
  save4.SetX(SCREEN_WIDTH/2 - save4.GetW()/2);
  save5.SetX(SCREEN_WIDTH/2 - save5.GetW()/2);

  selected = 0;
  left.SetX(save1.GetX() - BLOCK_WIDTH_OFFSET - left.GetW());
  left.SetY(save1.GetY() + save1.GetH()/2 - left.GetH()/2 + BLOCK_HEIGHT_OFFSET);
  right.SetX(save1.GetX() + save1.GetW() + BLOCK_WIDTH_OFFSET);
  right.SetY(save1.GetY() + save1.GetH()/2 - right.GetH()/2 + BLOCK_HEIGHT_OFFSET);

}

void SaveSelectionState::HandleEvents (GameEngine* game) {
  SDL_Event event;

	while (SDL_PollEvent(&event)) {

    HandleSelection(event);

    HandleEnter(event, game);

    HandleDelete(event);

    switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            game->SetState(new MenuState(game));
            break;
				}
				break;
		}

	}
}

void SaveSelectionState::Update (GameEngine* game) {

  UpdateBlockPositions();

}

void SaveSelectionState::Draw (GameEngine* game) {

  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game->renderer);

  selectsave.Draw(game->renderer);
  save1.Draw(game->renderer);
  save2.Draw(game->renderer);
  save3.Draw(game->renderer);
  save4.Draw(game->renderer);
  save5.Draw(game->renderer);

  left.Draw(game->renderer);
  right.Draw(game->renderer);

  SDL_RenderPresent(game->renderer);

}

void SaveSelectionState::HandleSelection (const SDL_Event& event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_UP:
          if (selected == 0) {
            selected = 4;
          }
          else {
            selected--;
          }
          break;
        case SDLK_DOWN:
          if (selected == 4) {
            selected = 0;
          }
          else {
            selected++;
          }
          break;
      }
      break;
  }
}

void SaveSelectionState::UpdateBlockPositions () {
  switch (selected) {
    case 0:
      left.SetX(save1.GetX() - BLOCK_WIDTH_OFFSET - left.GetW());
      left.SetY(save1.GetY() + save1.GetH()/2 - left.GetH()/2 + BLOCK_HEIGHT_OFFSET);
      right.SetX(save1.GetX() + save1.GetW() + BLOCK_WIDTH_OFFSET);
      right.SetY(save1.GetY() + save1.GetH()/2 - right.GetH()/2 + BLOCK_HEIGHT_OFFSET);
      break;
    case 1:
      left.SetX(save2.GetX() - BLOCK_WIDTH_OFFSET - left.GetW());
      left.SetY(save2.GetY() + save2.GetH()/2 - left.GetH()/2 + BLOCK_HEIGHT_OFFSET);
      right.SetX(save2.GetX() + save2.GetW() + BLOCK_WIDTH_OFFSET);
      right.SetY(save2.GetY() + save2.GetH()/2 - right.GetH()/2 + BLOCK_HEIGHT_OFFSET);
      break;
    case 2:
      left.SetX(save3.GetX() - BLOCK_WIDTH_OFFSET - left.GetW());
      left.SetY(save3.GetY() + save3.GetH()/2 - left.GetH()/2 + BLOCK_HEIGHT_OFFSET);
      right.SetX(save3.GetX() + save3.GetW() + BLOCK_WIDTH_OFFSET);
      right.SetY(save3.GetY() + save3.GetH()/2 - right.GetH()/2 + BLOCK_HEIGHT_OFFSET);
      break;
    case 3:
      left.SetX(save4.GetX() - BLOCK_WIDTH_OFFSET - left.GetW());
      left.SetY(save4.GetY() + save4.GetH()/2 - left.GetH()/2 + BLOCK_HEIGHT_OFFSET);
      right.SetX(save4.GetX() + save4.GetW() + BLOCK_WIDTH_OFFSET);
      right.SetY(save4.GetY() + save4.GetH()/2 - right.GetH()/2 + BLOCK_HEIGHT_OFFSET);
      break;
    case 4:
      left.SetX(save5.GetX() - BLOCK_WIDTH_OFFSET - left.GetW());
      left.SetY(save5.GetY() + save5.GetH()/2 - left.GetH()/2 + BLOCK_HEIGHT_OFFSET);
      right.SetX(save5.GetX() + save5.GetW() + BLOCK_WIDTH_OFFSET);
      right.SetY(save5.GetY() + save5.GetH()/2 - right.GetH()/2 + BLOCK_HEIGHT_OFFSET);
      break;
  }
}

void SaveSelectionState::UpdateSaveNames () {

  std::ifstream ifs1 ("data/saves/save1.txt", std::ios_base::in);
  std::ifstream ifs2 ("data/saves/save2.txt", std::ios_base::in);
  std::ifstream ifs3 ("data/saves/save3.txt", std::ios_base::in);
  std::ifstream ifs4 ("data/saves/save4.txt", std::ios_base::in);
  std::ifstream ifs5 ("data/saves/save5.txt", std::ios_base::in);

  std::string line;
  std::string line2;

  if (ifs1.is_open()) {
    getline(ifs1, line);
    save1.UpdateText(line);
    save1loaded = true;
  }

  if (ifs2.is_open()) {
    getline(ifs2, line);
    save2.UpdateText(line);
    save2loaded = true;
  }

  if (ifs3.is_open()) {
    getline(ifs3, line);
    save3.UpdateText(line);
    save3loaded = true;
  }

  if (ifs4.is_open()) {
    getline(ifs4, line);
    save4.UpdateText(line);
    save4loaded = true;
  }

  if (ifs5.is_open()) {
    getline(ifs5, line);
    save5.UpdateText(line);
    save5loaded = true;
  }

}

void SaveSelectionState::HandleEnter (const SDL_Event& event, GameEngine* game) {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_RETURN:
          switch (selected) {
            case 0:
              if (!save1loaded) {
                game->SetState(new CreationState(game, selected));
              }
              else {
                LoadSaveVars("data/saves/save1.txt");
                game->SetState(new PlayState(game, selected, room, lvl, str, def, vit, unspentPoints, hp, xp, r, g, b, items));
              }
              break;
            case 1:
              if (!save2loaded) {
                game->SetState(new CreationState(game, selected));
              }
              else {
                LoadSaveVars("data/saves/save2.txt");
                game->SetState(new PlayState(game, selected, room, lvl, str, def, vit, unspentPoints, hp, xp, r, g, b, items));
              }
              break;
            case 2:
              if (!save3loaded) {
                game->SetState(new CreationState(game, selected));
              }
              else {
                LoadSaveVars("data/saves/save3.txt");
                game->SetState(new PlayState(game, selected, room, lvl, str, def, vit, unspentPoints, hp, xp, r, g, b, items));
              }
              break;
            case 3:
              if (!save4loaded) {
                game->SetState(new CreationState(game, selected));
              }
              else {
                LoadSaveVars("data/saves/save4.txt");
                game->SetState(new PlayState(game, selected, room, lvl, str, def, vit, unspentPoints, hp, xp, r, g, b, items));
              }
              break;
            case 4:
              if (!save5loaded) {
                game->SetState(new CreationState(game, selected));
              }
              else {
                LoadSaveVars("data/saves/save5.txt");
                game->SetState(new PlayState(game, selected, room, lvl, str, def, vit, unspentPoints, hp, xp, r, g, b, items));
              }
              break;
          }
          break;
      }
      break;
  }
}

void SaveSelectionState::LoadSaveVars (std::string path) {
  items.clear();
  std::ifstream ifs(path, std::ios_base::in);
  getline (ifs, room);
  getline (ifs, room);
  ifs >> lvl >> str >> def >> vit >> unspentPoints >> hp >> xp >> r >> g >> b;
  getline (ifs, tmp);
  for (int i = 0; i < 7; i++) {
    getline (ifs, tmp);
    items.push_back(tmp);
  }
}

void SaveSelectionState::HandleDelete (const SDL_Event& event) {

  switch (event.type) {
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_BACKSPACE || event.key.keysym.sym == SDLK_DELETE) {
        switch (selected) {
          case 0:
            if (save1loaded) {
              remove("data/saves/save1.txt");
              save1.UpdateText("(empty)");
              save1.SetX(SCREEN_WIDTH/2 - save1.GetW()/2);
              save1loaded = false;
            }
            break;
          case 1:
            if (save2loaded) {
              remove("data/saves/save2.txt");
              save2.UpdateText("(empty)");
              save2.SetX(SCREEN_WIDTH/2 - save2.GetW()/2);
              save2loaded = false;
            }
            break;
          case 2:
            if (save3loaded) {
              remove("data/saves/save3.txt");
              save3.UpdateText("(empty)");
              save3.SetX(SCREEN_WIDTH/2 - save3.GetW()/2);
              save3loaded = false;
            }
            break;
          case 3:
            if (save4loaded) {
              remove("data/saves/save4.txt");
              save4.UpdateText("(empty)");
              save4.SetX(SCREEN_WIDTH/2 - save4.GetW()/2);
              save4loaded = false;
            }
            break;
          case 4:
            if (save5loaded) {
              remove("data/saves/save5.txt");
              save5.UpdateText("(empty)");
              save5.SetX(SCREEN_WIDTH/2 - save5.GetW()/2);
              save5loaded = false;
            }
            break;
        }
      }
      break;
  }
}