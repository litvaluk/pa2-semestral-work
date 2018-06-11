#ifndef __BAR_HEADER__
#define __BAR_HEADER__

#include "SDL2/SDL.h"
#include "graphicalobject.h"

class Bar : public GraphicalObject {

  public:

    /**
     * @brief Constructor.
     */
  	Bar (int x, int y, int w, int h, int r, int g, int b);

    void Draw (SDL_Renderer* renderer);

    /**
     * @brief Updates the bar according to given values.
     * @param current current value
     * @param max maximum value
     */
    void Update (int current, int max);

  private:

    SDL_Rect border;
    SDL_Rect fill;
    SDL_Rect bar;

    int maxWidth;

    int r;
    int g;
    int b;

};

#endif
