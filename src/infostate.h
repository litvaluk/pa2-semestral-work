#ifndef __INFOSTATE_HEADER__
#define __INFOSTATE_HEADER__

#include "SDL2/SDL.h"
#include "gameengine.h"
#include "gamestate.h"
#include "text.h"

#include <string>

class InfoState : public GameState {

  public:

    /**
     * @brief Constructor.
     * @param game pointer to a game engine
     * @param text text to be displayed
     */
  	InfoState (GameEngine* game, const std::string& text);

  	void HandleEvents (GameEngine* game);
  	void Update (GameEngine* game);
  	void Draw (GameEngine* game);

  private:

    Text infoText;

    Uint32 switchTime;
    Uint32 currentTime;

};

#endif
