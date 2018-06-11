#ifndef __GAMEENGINE_HEADER__
#define __GAMEENGINE_HEADER__

#include "SDL2/SDL.h"

class GameState;

class GameEngine {

  public:

    /**
     * @brief Constructor (sets state to NULL).
     */
    GameEngine () {
      state = NULL;
    }

    /**
     * @brief Initializes the game engine.
     */
  	void Init (const char* title, int w = 1280, int h = 720);

    /**
     * @brief Cleans the game engine.
     */
    void Clean ();

    /*!
     * @brief Sets the scene.
     * @param newState a pointer to a new state
     */
  	void SetState (GameState* newState);

    /**
     * @brief Handles user input, etc.
     */
  	void HandleEvents ();

    /**
     * @brief Updates the scene.
     */
    void Update ();

    /**
     * @brief Draws scene on the window.
     */
    void Draw ();

    /**
     * @brief Returns true if the game is running.
     * @return true if game is running, otherwise false
     */
  	bool Running () const {
      return running;
    }

    /**
     * @brief Quits the game (sets running to false).
     */
    void Quit () {
      running = false;
    }

    SDL_Renderer* renderer;

  private:

    SDL_Window* window;
    GameState* state;
    bool running;

};

#endif