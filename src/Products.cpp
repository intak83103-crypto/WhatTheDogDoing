#include "../include/Products.h"

#include "../include/IO.h"
#include "../include/Item.h"
#include "../include/User.h"

ProductDD::ProductDD() : Product("新的刀盾", 100) {}

void ProductDD::Apply(User& user) const {
  user.AddDD();
}


ProductSmallHealPotion::ProductSmallHealPotion() : Product("小治療藥水", 20) {}

void ProductSmallHealPotion::Apply(User& user) const {
  user.GetItem(ItemType::SmallHealPotion);
}


ProductSmallExpPotion::ProductSmallExpPotion() : Product("小經驗藥水", 200) {}

void ProductSmallExpPotion::Apply(User& user) const {
  user.GetItem(ItemType::SmallExpPotion);
}