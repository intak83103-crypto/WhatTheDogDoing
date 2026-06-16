#include "../include/Item.h"

#include "../include/IO.h"
#include "../include/User.h"

ItemInfo ItemDatabase::GetInfo(ItemType type) {
  if ( type == ItemType::SmallHealPotion ) {
    return {
      ItemType::SmallHealPotion,
      ItemTargetType::DogDoing,
      "小治療藥水",
      "可使用在刀盾身上，回復 20HP"
    };
  } else if ( type == ItemType::SmallExpPotion ) {
    return {
      ItemType::SmallExpPotion,
      ItemTargetType::DogDoing,
      "小經驗藥水",
      "可使用在刀盾身上，獲得50經驗"
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
  if ( type == ItemType::SmallHealPotion ) {
    DogDoing* dd = user.GetIndexOfDD(target);
    if ( dd == nullptr ) {
      return;
    }
    dd->Heal(20);
    CreatureInfo info = dd->GetCreatureInfo();
    IO::UseItem(GetInfo(type).name);
    IO::HealSuccess(info.name, info.hp);
  } else if ( type == ItemType::SmallExpPotion ) {
    DogDoing* dd = user.GetIndexOfDD(target);
    if ( dd == nullptr ) {
      return;
    }
    IO::UseItem(GetInfo(type).name);
    dd->AddExp(50);
    
  }
}
