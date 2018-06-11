#ifndef __GRAPHICALOBJECT_HEADER__
#define __GRAPHICALOBJECT_HEADER__

#include "SDL2/SDL.h"

class GraphicalObject {

  public:

    /**
     * @brief Default Constructor.
     */
  	GraphicalObject () = default;

    /**
     * @brief Default destructor.
     */
	  virtual ~GraphicalObject () = default;

    /**
     * @brief Draws the object.
     */
    virtual void Draw (SDL_Renderer* renderer) = 0;

    /**
     * @brief Sets the x coord of the object.
     */
    virtual void SetX (int x) {
      this->x = x;
    }

    /**
     * @brief Sets the y coord of the object.
     */
    virtual void SetY (int y) {
      this->y = y;
    }

    /**
     * @brief Returns the x coord of the object.
     * @return x coord of the object
     */
    int GetX () const {
      return x;
    }

    /**
     * @brief Returns the y coord of the object.
     * @return y coord of the object
     */
    int GetY () const {
      return y;
    }


  protected:

    int x;
    int y;

};

#endif
