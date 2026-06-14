#include "../include/Products.h"

#include "../include/IO.h"
#include "../include/Item.h"
#include "../include/User.h"

ProductDD::ProductDD() : Product("新的刀盾", 100) {}

void ProductDD::Apply(User& user) const {
  user.AddDD();
}

ProductHealPotion::ProductHealPotion() : Product("治療藥水", 20) {}

void ProductHealPotion::Apply(User& user) const {
  user.GetItem(ItemType::HealPotion);
}
