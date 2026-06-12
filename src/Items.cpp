#include "../include/Items.h"

#include "../include/User.h"



// 治療藥水

ItemHealPotion::ItemHealPotion() : Item("治療藥水", ItemType::HealPotion, ItemTargetType::DogDoing) {
  SetDetail("可使用在刀盾身上，每次回復 20HP");
}

void ItemHealPotion::Use(User& user, int target_dd) {
  DogDoing* target = user.GetIndexOfDD(target_dd);
  if ( target == nullptr ) {
    return;
  }
  target->Heal(20);
  CreatureInfo info = target->GetCreatureInfo();
  UsePrint(info);
}

void ItemHealPotion::UsePrint(CreatureInfo info) {
  IO::UseItem(GetName());
  IO::HealSuccess(info.name, info.hp);
}
