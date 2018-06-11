#ifndef __MENUSTATE_HEADER__
#define __MENUSTATE_HEADER__

#include "SDL2/SDL.h"
#include "gameengine.h"
#include "gamestate.h"
#include "text.h"
#include "block.h"

class MenuState : public GameState {

  public:

    /**
     * @brief Constructor.
     */
  	MenuState (GameEngine* game);

  	void HandleEvents (GameEngine* game);
  	void Update (GameEngine* game);
  	void Draw (GameEngine* game);

  private:

    Block left;
    Block right;

    Text name;
    Text start;
    Text exit;
    Text author;

    int selected;

};

#endif