#include "../include/Items.h"



// 治療藥水

ItemHealPotion::ItemHealPotion() : Item("治療藥水", ItemType::HealPotion) {}

void ItemHealPotion::Use(User& user) {
  UsePrint();
}
