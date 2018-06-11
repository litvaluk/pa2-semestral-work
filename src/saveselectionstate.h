#ifndef __SAVESELECTIONSTATE_HEADER__
#define __SAVESELECTIONSTATE_HEADER__

#include "SDL2/SDL.h"
#include "gameengine.h"
#include "gamestate.h"
#include "text.h"
#include "block.h"

#include <vector>
#include <string>

class SaveSelectionState : public GameState {

  public:

    /**
     * @brief Constructor.
     */
  	SaveSelectionState (GameEngine* game);

  	void HandleEvents(GameEngine* game);
  	void Update(GameEngine* game);
  	void Draw(GameEngine* game);

  private:

    /**
     * @brief Handles the arrows.
     * @param event event to capture the input to
     */
    void HandleSelection (const SDL_Event& event);

    /**
     * @brief Update the selection block positions.
     */
    void UpdateBlockPositions ();

    /**
     * @brief Update the names of the saves.
     */
    void UpdateSaveNames ();

    /**
     * @brief Handles the enter key.
     * @param event event to capture the input to
     */
    void HandleEnter (const SDL_Event& event, GameEngine* game);

    /**
     * @brief Loads the variables from the save.
     */
    void LoadSaveVars (std::string path);

    /**
     * @brief Handles the delete key.
     * @param event event to capture the input to
     */
    void HandleDelete (const SDL_Event& event);

    Text selectsave;

    Text save1;
    Text save2;
    Text save3;
    Text save4;
    Text save5;

    Block left;
    Block right;

    bool save1loaded;
    bool save2loaded;
    bool save3loaded;
    bool save4loaded;
    bool save5loaded;

    int selected;

    std::string room;
    int lvl, str, def, vit, unspentPoints, hp, xp, r, g, b;
    std::string tmp;
    std::vector<std::string> items;

};

#endif
