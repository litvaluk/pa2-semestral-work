#ifndef __GAMESTATE_HEADER__
#define __GAMESTATE_HEADER__

#include "gameengine.h"

class GameState {

  public:

    /**
     * @brief Default constructor.
     * @param game GameEngine pointer
     */
    GameState (GameEngine* game) {};

    /**
     * @brief Default destructor.
     */
    virtual ~GameState () = default;

    /**
     * @brief Handles input, etc of the scene.
     * @param game a pointer to a game engine
     */
  	virtual void HandleEvents (GameEngine* game) = 0;

    /**
     * @brief Updates the contents of the scene.
     * @param game a pointer to a game engine
     */
    virtual void Update (GameEngine* game) = 0;

    /**
     * @brief Draws the contents of the scene.
     * @param game a pointer to a game engine
     */
    virtual void Draw (GameEngine* game) = 0;

};

#endif