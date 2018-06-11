#ifndef __CREATIONSTATE_HEADER__
#define __CREATIONSTATE_HEADER__

#include "SDL2/SDL.h"
#include "gameengine.h"
#include "gamestate.h"
#include "block.h"
#include "text.h"

#include <string>

class CreationState : public GameState {

  public:

    /**
     * @brief Constructor.
     */
  	CreationState (GameEngine* game, int saveNumber);

  	void HandleEvents (GameEngine* game);
  	void Update (GameEngine* game);
  	void Draw (GameEngine* game);

  private:

    /**
     * @brief Updates the left and right selection blocks.
     */
    void UpdateSelectionBlocks ();

    /**
     * @brief Updates the color of the player block preview.
     */
    void UpdateColor ();

    /**
     * @brief Increases selected attribute/color.
     */
    void IncreaseSelection ();

    /**
     * @brief Decreases selected attribute/color.
     */
    void DecreaseSelection ();

    Text colorText;
    Text strengthText;
    Text defenseText;
    Text vitalityText;
    Text unspentPointsText;

    Block block;
    Block innerBlock;

    Block left;
    Block right;

    int str, def, vit, unspentPoints;

    int selection;
    int saveNumber;

    std::string colors[4] = {"white", "red", "green", "blue"};
    int selectedColor;

};

#endif
