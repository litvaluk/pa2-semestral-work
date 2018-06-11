/**
 * @author Lukáš Litvan
 * @version 1.0
 * @date 18.5.2018
 * @mainpage Mazed - Graphical RPG game
 */

#include "gameengine.h"
#include "menustate.h"

#include <ctime>
#include <iostream>

#define FPS 60

int main (void) {

  srand(time(NULL));

  Uint32 frameStart;
  int frameTime;

  GameEngine game;
  game.Init("Mazed");
  game.SetState(new MenuState(&game));

  while (game.Running()) {

    frameStart = SDL_GetTicks();

    game.HandleEvents();
    game.Update();
    game.Draw();

    frameTime = SDL_GetTicks() - frameStart;
   	if(1000/FPS > frameTime) SDL_Delay(1000/FPS - frameTime);

  }

  game.Clean();

  return 0;

}
