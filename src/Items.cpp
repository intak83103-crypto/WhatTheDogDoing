#include "../include/Items.h"

ItemHealPotion::ItemHealPotion() : Item("治療藥水") {}

void ItemHealPotion::Use(User& user) {
  UsePrint();
}
