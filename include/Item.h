#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "DisplayData.h"

class User;

enum class ItemType {
  HealPotion, None
};
enum class ItemTargetType{
  DogDoing, None
};

class Item {
private:
  std::string name;
  ItemType type = ItemType::None;
  ItemTargetType target = ItemTargetType::None;
  std::string detail;

public:
  Item();
  Item(std::string name, ItemType item, ItemTargetType target);
  const std::string& GetDetail() ;
  void SetDetail(const std::string& detail);
  virtual ~Item();
  virtual void Use(User& user, int target = -1) = 0;
  virtual std::string GetName();
  ItemTargetType GetItemTargetType() const;
  ItemType GetItemType() const;
};

#endif
