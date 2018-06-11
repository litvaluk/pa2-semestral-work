#ifndef __PROXIMITYBLOCK_HEADER__
#define __PROXIMITYBLOCK_HEADER__

#include "SDL2/SDL.h"
#include "block.h"

class ProximityBlock : public Block {

  public:

    /**
     * @brief Constructor.
     * @param x x coord of the treasure
     * @param y y coord of the treasure
     * @param w width of the treasure
     * @param h height of the treasure
     * @param rNot red component of the treasure color when not in proximity.
     * @param gNot green component of the treasure color when not in proximity.
     * @param bNot blue component of the treasure color when not in proximity.
     * @param rProx red component of the treasure color when in proximity.
     * @param gProx green component of the treasure color when in proximity.
     * @param bProx blue component of the treasure color when in proximity.
     */
  	ProximityBlock (int x, int y, int w, int h, int rNot, int gNot, int bNot, int rProx, int gProx, int bProx);

    /**
     * @brief Returns true if the given block is in proximity..
     * @param block Block object to check the proximity
     * @return true if in proximity, otherwise false
     */
  	bool ProximityCheck (const Block& block);

  private:

    /**
     * @brief Sets the color.
     * @param r red color component
     * @param g green color component
     * @param b blue color component
     */
    void SetColor (int r, int g, int b);

    int rNot;
    int gNot;
    int bNot;
    int rProx;
    int gProx;
    int bProx;

};

#endif
