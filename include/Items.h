#ifndef ITEMS_H
#define ITEMS_H

#include "Item.h"

class ItemHealPotion : public Item {
public:
  ItemHealPotion();
  void Use(User& user, int target__dd) override;
  void UsePrint(CreatureInfo info);
};

#endif

