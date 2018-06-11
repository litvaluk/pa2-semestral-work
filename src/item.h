#ifndef __ITEM_HEADER__
#define __ITEM_HEADER__

#include "SDL2/SDL.h"

#include <string>

class Item {

  public:

    /**
     * @brief Constructor.
     */
  	Item (const std::string& name, int stat, char type);

    /**
     * @brief Returns name of the item.
     * @return item name
     */
    std::string GetName () const;

    /**
     * @brief Returns value of the item stat.
     * @return item stat
     */
    int GetStat () const;

    /**
     * @brief Returns the type of the item.
     * @return item type
     */
    char GetType () const;

  private:

    std::string name;
    int stat;
    char type;

};

#endif
