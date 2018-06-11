#ifndef __TEXT_HEADER__
#define __TEXT_HEADER__

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "graphicalobject.h"

#include <string>

class Text : public GraphicalObject {

  public:

    /**
     * @brief Constructor.
     * @param x x coord of the text
     * @param y y coord of the text
     * @param text string to be displayed
     * @param color color
     * @param font font
     * @param renderer game renderer
     */
  	Text(int x, int y, std::string text, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);

    /**
     * @brief Destructor.
     */
  	~Text();

    void Draw (SDL_Renderer* Renderer);

    /**
     * @brief Changes the displayed text.
     * @param text string to be displayed
     */
    void UpdateText (std::string text);


    void SetX (int x) {
      this->x = rect.x = x;
    }

    void SetY (int y) {
      this->y = rect.y = y;
    }

    /**
     * @brief Returns the width of the text.
     * @return width of the text
     */
    int GetW () const {
      return rect.w;
    }

    /**
     * @brief Returns the height of the text.
     * @return height of the text
     */
    int GetH () const {
      return rect.h;
    }

  private:

    /**
     * @brief Frees the texture variable.
     */
    void Free ();

    SDL_Texture* texture;
    SDL_Rect rect;

    SDL_Color color;
    TTF_Font* font;
    SDL_Renderer* renderer;

};

#endif
