#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "gameengine.h"
#include "gamestate.h"

TTF_Font* coolvetica20;
TTF_Font* coolvetica30;
TTF_Font* coolvetica40;
TTF_Font* coolvetica35;
TTF_Font* coolvetica25;
TTF_Font* coolvetica100;

void GameEngine::Init (const char* title, int w, int h) {

  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
  TTF_Init();
  coolvetica20 = TTF_OpenFont("data/fonts/coolvetica.ttf", 20);
  coolvetica25 = TTF_OpenFont("data/fonts/coolvetica.ttf", 25);
  coolvetica30 = TTF_OpenFont("data/fonts/coolvetica.ttf", 30);
  coolvetica40 = TTF_OpenFont("data/fonts/coolvetica.ttf", 40);
  coolvetica35 = TTF_OpenFont("data/fonts/coolvetica.ttf", 35);
  coolvetica100 = TTF_OpenFont("data/fonts/coolvetica.ttf", 100);
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  running = true;

}

void GameEngine::Clean () {

  if (state != NULL) {
    delete state;
  }

  TTF_CloseFont(coolvetica20);
  TTF_CloseFont(coolvetica25);
  TTF_CloseFont(coolvetica30);
  TTF_CloseFont(coolvetica40);
  TTF_CloseFont(coolvetica35);
  TTF_CloseFont(coolvetica100);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();

}

void GameEngine::SetState (GameState* newState) {

  if (state != NULL) {
    delete state;
  }
  state = newState;

}

void GameEngine::HandleEvents () {

  state->HandleEvents(this);

}

void GameEngine::Update () {

  state->Update(this);

}

void GameEngine::Draw () {

  state->Draw(this);

}