#ifndef __MONSTER_HEADER__
#define __MONSTER_HEADER__

#include "SDL2/SDL.h"
#include "block.h"
#include "proximityblock.h"

#include <string>
#include <vector>

class Monster : public Block {

  public:

    /**
     * @brief Constructor.
     * @param name name of the monster
     * @param str attribute of the monster
     * @param def attribute of the monster
     * @param vit attribute of the monster
     * @param r red component of the monster color
     * @param g green component of the monster color
     * @param b blue component of the monster color
     */
  	Monster (const std::string& name, int str, int def, int vit, int r, int g, int b);

    /**
     * @brief Moves the monster with collision checking.
     * @param walls vector with wall objects
     * @param treasures vector with treasure objects
     * @param monsters vector of monster objects
     * @param nextRoomBlock pointer to a next room block object
     */
    void Move (const std::vector<Block>& walls,
               const std::vector<ProximityBlock>& treasures,
               const std::vector<Monster>& monsters,
               ProximityBlock* nextRoomBlock);

   /**
    * @brief Updates the monster direction every ~1 sec.
    */
    void UpdateDirection ();

    /**
     * @brief Computes and returns hitpoints damage dealt by the monster.
     * @param playerStr strength of the player
     * @param playerDef defense of the player
     * @param playerVit vitality of the player
     * @param playerWeaponStr strength of player's weapon
     * @param playerArmorDef defense of player's armor
     * @param playerHp hit points of the player
     * @return lost hit points
     */
    int GetLostHp (int playerStr, int playerDef, int playerVit, int playerWeaponStr, int playerArmorDef, int playerHp);

    /**
     * @brief Computes and returns gained xp from the moster.
     * @return gained xp
     */
    int GetGainedXp () const;

    /**
     * @brief Sets x coord of the monster.
     */
    void SetX (int x);

    /**
     * @brief Sets y coord of the monster.
     */
    void SetY (int y);

  private:

    /**
     * @brief Updates the direction of the monster immediately.
     */
    void UpdateDirectionNow ();

    std::string name;
    int velX, velY, speed;
    int str, def, vit;
    int hp;
    int direction;

    unsigned long long lastTime;
    unsigned long long randomTime;

};

#endif
