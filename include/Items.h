#ifndef ITEMS_H
#define ITEMS_H

#include "Item.h"

class ItemHealPotion : public Item {
public:
  ItemHealPotion();
  void Use(User& user) override;
};

#endif
