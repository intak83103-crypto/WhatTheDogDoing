#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "DisplayData.h"

class User;

enum class ItemType {
  HealPotion, None
};
enum class ItemTargetType {
  DogDoing, None
};

struct ItemInfo {
  ItemType type;
  ItemTargetType target;
  std::string name;
  std::string detail;
};

class ItemDatabase {
public:
  static ItemInfo GetInfo(ItemType type);
  static void UseItem(User& user, ItemType type, int target = -1);
};

#endif
