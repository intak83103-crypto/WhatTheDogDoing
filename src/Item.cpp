#include "../include/Item.h"

#include "../include/IO.h"
#include "../include/User.h"

ItemInfo ItemDatabase::GetInfo(ItemType type) {
  if ( type == ItemType::HealPotion ) {
    return {
      ItemType::HealPotion,
      ItemTargetType::DogDoing,
      "治療藥水",
      "可使用在刀盾身上，每次回復 20HP"
    };
  }
  return {
    ItemType::None,
    ItemTargetType::None,
    "未知道具",
    ""
  };
}

void ItemDatabase::UseItem(User& user, ItemType type, int target) {
  if ( type == ItemType::HealPotion ) {
    DogDoing* dd = user.GetIndexOfDD(target);
    if ( dd == nullptr ) {
      return;
    }
    dd->Heal(20);
    CreatureInfo info = dd->GetCreatureInfo();
    IO::UseItem(GetInfo(type).name);
    IO::HealSuccess(info.name, info.hp);
  }
}
