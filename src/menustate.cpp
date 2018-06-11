#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "gameengine.h"
#include "gamestate.h"
#include "menustate.h"
#include "playstate.h"
#include "creationstate.h"
#include "saveselectionstate.h"
#include "text.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BLOCK_WIDTH_OFFSET 30
#define BLOCK_HEIGHT_OFFSET 2

extern TTF_Font* coolvetica100;
extern TTF_Font* coolvetica40;
extern TTF_Font* coolvetica20;

MenuState::MenuState (GameEngine* game)
: GameState(game),
left(Block(10, 10, 20, 20, 255, 0, 0)),
right(Block(10, 10, 20, 20, 255, 0, 0)),
name(Text(0, 100, "Mazed", {255, 255, 255, 0}, coolvetica100, game->renderer)),
start(Text(0, 350, "Start", {255, 255, 255, 0}, coolvetica40, game->renderer)),
exit(Text(0, 420, "Exit", {255, 255, 255, 0}, coolvetica40, game->renderer)),
author(Text(SCREEN_WIDTH-158, SCREEN_HEIGHT-30, "Lukáš Litvan, 2018", {255, 255, 255, 0}, coolvetica20, game->renderer)) {

  name.SetX(SCREEN_WIDTH/2 - name.GetW()/2);
  start.SetX(SCREEN_WIDTH/2 - start.GetW()/2);
  exit.SetX(SCREEN_WIDTH/2 - exit.GetW()/2);

  selected = 0;
  left.SetX(start.GetX() - BLOCK_WIDTH_OFFSET - left.GetW());
  left.SetY(start.GetY() + start.GetH()/2 - left.GetH()/2 + BLOCK_HEIGHT_OFFSET);
  right.SetX(start.GetX() + start.GetW() + BLOCK_WIDTH_OFFSET);
  right.SetY(start.GetY() + start.GetH()/2 - right.GetH()/2 + BLOCK_HEIGHT_OFFSET);

}

void MenuState::HandleEvents (GameEngine* game) {

  SDL_Event event;

	while (SDL_PollEvent(&event)) {

    switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
          case SDLK_RETURN:
            if (selected == 0) {
              game->SetState(new SaveSelectionState(game));
            }
            else {
              game->Quit();
            }
            break;
          case SDLK_ESCAPE:
            game->Quit();
            break;
          case SDLK_UP:
            if (selected == 1) {
              selected = 0;
              left.SetX(start.GetX() - BLOCK_WIDTH_OFFSET - left.GetW());
              left.SetY(start.GetY() + start.GetH()/2 - left.GetH()/2 + BLOCK_HEIGHT_OFFSET);
              right.SetX(start.GetX() + start.GetW() + BLOCK_WIDTH_OFFSET);
              right.SetY(start.GetY() + start.GetH()/2 - right.GetH()/2 + BLOCK_HEIGHT_OFFSET);
            }
            break;
          case SDLK_DOWN:
            if (selected == 0) {
              selected = 1;
              left.SetX(exit.GetX() - BLOCK_WIDTH_OFFSET - left.GetW());
              left.SetY(exit.GetY() + exit.GetH()/2 - left.GetH()/2 + BLOCK_HEIGHT_OFFSET);
              right.SetX(exit.GetX() + exit.GetW() + BLOCK_WIDTH_OFFSET);
              right.SetY(exit.GetY() + exit.GetH()/2 - right.GetH()/2 + BLOCK_HEIGHT_OFFSET);
            }
            break;
				}
				break;
		}

	}

}

void MenuState::Update (GameEngine* game) {

}

void MenuState::Draw (GameEngine* game) {

  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game->renderer);

  name.Draw(game->renderer);
  start.Draw(game->renderer);
  exit.Draw(game->renderer);
  author.Draw(game->renderer);
  left.Draw(game->renderer);
  right.Draw(game->renderer);

  SDL_RenderPresent(game->renderer);

}