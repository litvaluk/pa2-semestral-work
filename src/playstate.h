#ifndef __PLAYSTATE_HEADER__
#define __PLAYSTATE_HEADER__

#include "SDL2/SDL.h"
#include "gameengine.h"
#include "gamestate.h"
#include "block.h"
#include "player.h"
#include "proximityblock.h"
#include "monster.h"
#include "bar.h"
#include "text.h"
#include "item.h"

#include <vector>
#include <string>

class PlayState : public GameState {

  public:

    /**
     * @brief Constructor, new game.
     * @param game GameEngine pointer
     * @param saveNumber save number
     * @param str strength
     * @param def defense
     * @param vit vitality
     * @param r red component of the player color
     * @param g green component of the player color
     * @param b blue component of the player color
     */
  	PlayState (GameEngine* game, int saveNumber, int str, int def, int vit, int r, int g, int b);

    /**
     * @brief Constructor, loaded game.
     * @param game GameEngine pointer
     * @param saveNumber save number
     * @param room name of the room
     * @param lvl level
     * @param str strength
     * @param def defense
     * @param vit vitality
     * @param unspentPoints unspent points
     * @param hp hit points
     * @param xp experience points
     * @param r red component of the player color
     * @param g green component of the player color
     * @param b blue component of the player color
     * @param items vector of items (equipped weapon and armor, backpack items)
     */
    PlayState (GameEngine* game, int saveNumber, const std::string& room, int lvl, int str, int def, int vit, int unspentPoints, int hp, int xp, int r, int g, int b, const std::vector<std::string>& items);

    /**
     * @brief Destructor.
     */
  	~PlayState ();

  	void HandleEvents (GameEngine* game);
  	void Update (GameEngine* game);
  	void Draw (GameEngine* game);



  private:

    /**
     * @brief Loads the room from a file.
     * @param src path to the text file with the room definition
     */
    void LoadRoom (const char* src);

    /**
     * @brief Loads the items from a file.
     * @param src path to the text file with the item list
     */
    void LoadItemList (const char* src);

    /**
     * @brief Loads the monsters from a file.
     * @param src path to the text file with the monster list
     */
    void LoadMonsterList (const char* src);

    /**
     * @brief Switches to a different room specified by the path to the file.
     * @param src path to the text file with the room to switch to
     */
    void SwitchRoom (const char* target);

    /**
     * @brief Increases the level and adds one unspent point.
     */
    void LevelUp ();

    /**
     * @brief Return the pointer to an item from the backpack at given index.
     * @param x backpack index
     * @return pointer to an item from the backpack
     */
    Item* GetItemFromBackpack (int x);

    /**
     * @brief Pushes an item to the backpack.
     * @param item pointer to an item
     * @return true if the push was succesful, false if not
     */
    bool PushItemToBackpack (Item* item);

    /**
     * @brief Destroys an item to the backpack.
     * @param x backpack index
     * @return true if the destruction was succesful, false if not
     */
    bool DestroyItemFromBackpack (int x);

    /**
     * @brief Uses an item in backpack at given index.
     * @param x backpack index
     */
    void UseItem (int x);

    /**
     * @brief Draws the UI (bars, texts).
     */
    void DrawUI ();

    /**
     * @brief Updates the backpack text.
     */
    void UpdateBackpackText ();

    /**
     * @brief Handles the backpack controls.
     */
    void HandleBackpackEvents (SDL_Event& event);

    /**
     * @brief Return the pointer to an item from the backpack with specified name.
     * @param name name of the item
     * @return pointer to an item from the backpack
     */
    Item* GetItem (const std::string& name) const;

    /**
     * @brief Saves the game.
     */
    void Save ();

    int str, def, vit, xp, maxXp, lvl, unspentPoints, r, g, b, weaponStr, armorDef, hp, maxHp;

    GameEngine* game;

    std::vector<Block> walls;
    std::vector<ProximityBlock> treasures;
    std::vector<Item*> itemList;
    Item* backpack[5] = {NULL, NULL, NULL, NULL, NULL};
    std::vector<Monster> monsterList;
    std::vector<Monster> monsters;

    Player* player;

    Item* equippedArmor;
    Item* equippedWeapon;

    ProximityBlock* nextRoomBlock;
    std::string currentRoom;
    std::string nextRoom;

    Bar hpBar;
    Bar xpBar;

    Block backpackBlock;

    Text strengthText;
    Text defenseText;
    Text vitalityText;

    Text hpText;
    Text xpText;
    Text lvlText;

    Text unspentPointsText;

    Text equippedText;
    Text equippedArmorText;
    Text equippedWeaponText;

    Text backpackText;
    Text backpackFirstText;
    Text backpackSecondText;
    Text backpackThirdText;
    Text backpackFourthText;
    Text backpackFifthText;

    int itemSelected;
    bool backpackSelection;
    int saveNumber;

};

#endif
