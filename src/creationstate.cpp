#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "gameengine.h"
#include "gamestate.h"
#include "creationstate.h"
#include "playstate.h"
#include "menustate.h"
#include "text.h"
#include "block.h"

#include <string>
#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BLOCK_SIZE 210
#define INNER_BLOCK_SIZE 70
#define BLOCK_X_OFFSET 300
#define TEXT_X_OFFSET 100
#define SELECTION_BLOCK_SIZE 20
#define SELECTION_BLOCK_OFFSET 3

extern TTF_Font* coolvetica35;

CreationState::CreationState (GameEngine* game, int saveNumber)
: GameState(game),
colorText(Text(SCREEN_WIDTH/2 + TEXT_X_OFFSET, 0, "color: white", {255, 255, 255, 0}, coolvetica35, game->renderer)),
strengthText(Text(SCREEN_WIDTH/2 + TEXT_X_OFFSET, 0, "strength: 3", {255, 255, 255, 0}, coolvetica35, game->renderer)),
defenseText(Text(SCREEN_WIDTH/2 + TEXT_X_OFFSET, 0, "defense: 3", {255, 255, 255, 0}, coolvetica35, game->renderer)),
vitalityText(Text(SCREEN_WIDTH/2 + TEXT_X_OFFSET, 0, "vitality: 3", {255, 255, 255, 0}, coolvetica35, game->renderer)),
unspentPointsText(Text(SCREEN_WIDTH/2 + TEXT_X_OFFSET, 0, "unspent points: 5", {255, 255, 255, 0}, coolvetica35, game->renderer)),
block(Block(SCREEN_WIDTH/2 - BLOCK_SIZE/2 - BLOCK_X_OFFSET, SCREEN_HEIGHT/2 - BLOCK_SIZE/2, BLOCK_SIZE, BLOCK_SIZE, 255, 255, 255)),
innerBlock(Block(SCREEN_WIDTH/2 - INNER_BLOCK_SIZE/2 - BLOCK_X_OFFSET, SCREEN_HEIGHT/2 - INNER_BLOCK_SIZE/2, INNER_BLOCK_SIZE, INNER_BLOCK_SIZE, 0, 0, 0)),
left(Block(0, 0, SELECTION_BLOCK_SIZE, SELECTION_BLOCK_SIZE, 255, 0, 0)),
right(Block(0, 0, SELECTION_BLOCK_SIZE, SELECTION_BLOCK_SIZE, 255, 0, 0)) {

  this->saveNumber = saveNumber;

  unspentPoints = 5;
  str = def = vit = 3;
  selectedColor = 0;
  selection = 0;

  defenseText.SetY(SCREEN_HEIGHT/2 - defenseText.GetH()/2 + 20);
  strengthText.SetY(defenseText.GetY() - 45);
  vitalityText.SetY(defenseText.GetY() + 45);
  colorText.SetY(defenseText.GetY() - 90);
  unspentPointsText.SetY(defenseText.GetY() + 150);

  left.SetX(colorText.GetX() - 40);
  left.SetY(colorText.GetY() + colorText.GetH()/2 - left.GetH()/2 + SELECTION_BLOCK_OFFSET);
  right.SetX(colorText.GetX() + colorText.GetW() + 40 - right.GetW());
  right.SetY(colorText.GetY() + colorText.GetH()/2 - right.GetH()/2 + SELECTION_BLOCK_OFFSET);

}

void CreationState::HandleEvents (GameEngine* game) {

  SDL_Event event;

	while (SDL_PollEvent(&event)) {

    switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
          case SDLK_RETURN:
            if (unspentPoints == 0) {
              if (selectedColor == 0) {
                game->SetState(new PlayState(game, saveNumber, str, def, vit, 255, 255, 255));
                return;
              }
              if (selectedColor == 1) {
                game->SetState(new PlayState(game, saveNumber, str, def, vit, 255, 0, 0));
                return;
              }
              if (selectedColor == 2) {
                game->SetState(new PlayState(game, saveNumber, str, def, vit, 0, 255, 0));
                return;
              }
              if (selectedColor == 3) {
                game->SetState(new PlayState(game, saveNumber, str, def, vit, 0, 0, 255));
                return;
              }
            }
            break;
          case SDLK_ESCAPE:
            game->SetState(new MenuState(game));
            break;
          case SDLK_UP:
            if (selection == 0) {
              selection = 0;
            }
            else {
              selection--;
              UpdateSelectionBlocks();
            }
            break;
          case SDLK_DOWN:
            if (selection == 3) {
              selection = 3;
            }
            else {
              selection++;
              UpdateSelectionBlocks();
            }
            break;
          case SDLK_LEFT:
            DecreaseSelection();
            break;
          case SDLK_RIGHT:
            IncreaseSelection();
            break;
				}
				break;
		}

	}

}

void CreationState::Update (GameEngine* game) {

}

void CreationState::Draw (GameEngine* game) {

  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game->renderer);

  colorText.Draw(game->renderer);
  strengthText.Draw(game->renderer);
  defenseText.Draw(game->renderer);
  vitalityText.Draw(game->renderer);
  unspentPointsText.Draw(game->renderer);

  block.Draw(game->renderer);
  innerBlock.Draw(game->renderer);

  left.Draw(game->renderer);
  right.Draw(game->renderer);

  SDL_RenderPresent(game->renderer);

}

void CreationState::UpdateSelectionBlocks () {
  switch (selection) {
    case 0:
      left.SetY(colorText.GetY() + colorText.GetH()/2 - left.GetH()/2 + SELECTION_BLOCK_OFFSET);
      right.SetX(colorText.GetX() + colorText.GetW() + 40 - right.GetW());
      right.SetY(colorText.GetY() + colorText.GetH()/2 - right.GetH()/2 + SELECTION_BLOCK_OFFSET);
      break;
    case 1:
      left.SetY(strengthText.GetY() + strengthText.GetH()/2 - left.GetH()/2 + SELECTION_BLOCK_OFFSET);
      right.SetX(strengthText.GetX() + strengthText.GetW() + 40 - right.GetW());
      right.SetY(strengthText.GetY() + strengthText.GetH()/2 - right.GetH()/2 + SELECTION_BLOCK_OFFSET);
      break;
    case 2:
      left.SetY(defenseText.GetY() + defenseText.GetH()/2 - left.GetH()/2 + SELECTION_BLOCK_OFFSET);
      right.SetX(defenseText.GetX() + defenseText.GetW() + 40 - right.GetW());
      right.SetY(defenseText.GetY() + defenseText.GetH()/2 - right.GetH()/2 + SELECTION_BLOCK_OFFSET);
      break;
    case 3:
      left.SetY(vitalityText.GetY() + vitalityText.GetH()/2 - left.GetH()/2 + SELECTION_BLOCK_OFFSET);
      right.SetX(vitalityText.GetX() + vitalityText.GetW() + 40 - right.GetW());
      right.SetY(vitalityText.GetY() + vitalityText.GetH()/2 - right.GetH()/2 + SELECTION_BLOCK_OFFSET);
      break;
  }
}

void CreationState::IncreaseSelection () {

  switch (selection) {
    case 0:
      if (selectedColor == 3) {
        selectedColor = 0;
      }
      else {
        selectedColor++;
      }
      colorText.UpdateText("color: " + colors[selectedColor]);
      UpdateColor();
      UpdateSelectionBlocks();
      break;
    case 1:
      if (unspentPoints > 0) {
        str++;
        unspentPoints--;
        strengthText.UpdateText("strength: " + std::to_string(str));
        unspentPointsText.UpdateText("unspent points: " + std::to_string(unspentPoints));
        UpdateSelectionBlocks();
      }
      break;
    case 2:
      if (unspentPoints > 0) {
        def++;
        unspentPoints--;
        defenseText.UpdateText("defense: " + std::to_string(def));
        unspentPointsText.UpdateText("unspent points: " + std::to_string(unspentPoints));
        UpdateSelectionBlocks();
      }
      break;
    case 3:
      if (unspentPoints > 0) {
        vit++;
        unspentPoints--;
        vitalityText.UpdateText("vitality: " + std::to_string(vit));
        unspentPointsText.UpdateText("unspent points: " + std::to_string(unspentPoints));
        UpdateSelectionBlocks();
      }
      break;
  }

}

void CreationState::DecreaseSelection () {

  switch (selection) {
    case 0:
      if (selectedColor == 0) {
        selectedColor = 3;
      }
      else {
        selectedColor--;
      }
      colorText.UpdateText("color: " + colors[selectedColor]);
      UpdateColor();
      UpdateSelectionBlocks();
      break;
    case 1:
      if (str > 3) {
        str--;
        unspentPoints++;
        strengthText.UpdateText("strength: " + std::to_string(str));
        unspentPointsText.UpdateText("unspent points: " + std::to_string(unspentPoints));
        UpdateSelectionBlocks();
      }
      break;
    case 2:
      if (def > 3) {
        def--;
        unspentPoints++;
        defenseText.UpdateText("defense: " + std::to_string(def));
        unspentPointsText.UpdateText("unspent points: " + std::to_string(unspentPoints));
        UpdateSelectionBlocks();
      }
      break;
    case 3:
      if (vit > 3) {
        vit--;
        unspentPoints++;
        vitalityText.UpdateText("vitality: " + std::to_string(vit));
        unspentPointsText.UpdateText("unspent points: " + std::to_string(unspentPoints));
        UpdateSelectionBlocks();
      }
      break;
  }

}

void CreationState::UpdateColor () {

  switch (selectedColor) {
    case 0:
      block.SetColor(255, 255, 255);
      break;
    case 1:
      block.SetColor(255, 0, 0);
      break;
    case 2:
      block.SetColor(0, 255, 0);
      break;
    case 3:
      block.SetColor(0, 0, 255);
      break;
  }

}
