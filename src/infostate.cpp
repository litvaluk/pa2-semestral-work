#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "gameengine.h"
#include "gamestate.h"
#include "text.h"
#include "infostate.h"
#include "menustate.h"

#include <string>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

extern TTF_Font* coolvetica100;

InfoState::InfoState (GameEngine* game, const std::string& text)
:GameState(game),
infoText(Text(0, 0, text, {255, 255, 255, 0}, coolvetica100, game->renderer)) {
  infoText.SetX(SCREEN_WIDTH/2 - infoText.GetW()/2);
  infoText.SetY(SCREEN_HEIGHT/2 - infoText.GetH()/2);
  switchTime = SDL_GetTicks();
  currentTime = SDL_GetTicks();
}

void InfoState::HandleEvents (GameEngine* game) {

  SDL_Event event;

	while (SDL_PollEvent(&event)) {

    switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;
		}
	}

}

void InfoState::Update (GameEngine* game) {

  currentTime = SDL_GetTicks();

  if (currentTime > switchTime + 3000) {
    game->SetState(new MenuState(game));
  }

}

void InfoState::Draw (GameEngine* game) {

  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game->renderer);

  infoText.Draw(game->renderer);

  SDL_RenderPresent(game->renderer);

}