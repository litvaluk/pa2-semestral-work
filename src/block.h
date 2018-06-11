#ifndef __BLOCK_HEADER__
#define __BLOCK_HEADER__

#include "SDL2/SDL.h"
#include "graphicalobject.h"

class Block : public GraphicalObject {

  public:

    /**
     * @brief Constructor.
     * @param x x coord of the block
     * @param y y coord of the block
     * @param w width of the block
     * @param h height of the block
     * @param r red component of the block color
     * @param g green component of the block color
     * @param b blue component of the block color
     */
  	Block(int x, int y, int w, int h, int r, int g, int b);

    /**
     * @brief Destructor.
     */
  	virtual ~Block() = default;

    virtual void Draw (SDL_Renderer* renderer);

    /**
     * @brief Returns true if collides with another block.
     */
    bool CollidesWith (const Block& block) const;

    void SetX (int x);

    void SetY (int y);

    /**
     * @brief Returns the width of the block.
     * @return width of the block
     */
    int GetW () const;

    /**
     * @brief Returns the height of the block.
     * @return height of the block
     */
    int GetH () const;

    /**
     * @brief Sets the color of the block.
     * @param r red component of the block color
     * @param g green component of the block color
     * @param b blue component of the block color
     */
    void SetColor (int r, int g, int b);

    SDL_Rect rect;
    int r;
    int g;
    int b;

};

#endif
