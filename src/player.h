#ifndef __PLAYER_HEADER__
#define __PLAYER_HEADER__

#include "SDL2/SDL.h"
#include "block.h"
#include "proximityblock.h"

#include <vector>

class Player : public Block {

  public:

    /**
     * @brief Constructor.
     * @param x x coord of the player
     * @param y y coord of the player
     * @param w width of the player
     * @param h height of the player
     * @param r red component of the player color
     * @param g green component of the player color
     * @param b blue component of the player color
     */
  	Player (int x, int y, int w, int h, int r, int g, int b);

    /**
     * @brief Moves the player with collision checking.
     * @param walls vector with wall objects
     * @param treasures vector with treasure objects
     * @param nextRoomBlock pointer to a next room block object
     */
    void Move (const std::vector<Block>& walls, const std::vector<ProximityBlock>& treasures, ProximityBlock* nextRoomBlock);

    /**
     * @brief Handles the user input.
     * @param event event to capture the input to
     */
    void HandleEvents (const SDL_Event& event);

    void Draw (SDL_Renderer* renderer);

    /**
     * @brief Sets the x and y velocity to 0.
     */
    void ResetVelocity ();

  private:

    SDL_Rect innerRect;

    int velX;
    int velY;

};

#endif
