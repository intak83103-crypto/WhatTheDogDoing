#include "../include/Products.h"

#include "../include/IO.h"
#include "../include/Items.h"
#include "../include/User.h"

ProductDD::ProductDD() : Product("新的刀盾", 100) {}

void ProductDD::Apply(User& user) const {
  user.AddDD();
}

ProductHealPotion::ProductHealPotion() : Product("治療藥水", 20) {}

void ProductHealPotion::Apply(User& user) const {
  IO::PrintDot(9);
  user.GetItem(new ItemHealPotion());
}
