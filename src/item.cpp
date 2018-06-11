#include "SDL2/SDL.h"

#include "item.h"

Item::Item (const std::string& name, int stat, char type)
: name(name), stat(stat), type(type) {}

std::string Item::GetName () const {
  return name;
}

int Item::GetStat () const {
  return stat;
}

char Item::GetType () const {
  return type;
}
