#ifndef ITEM_H
#define ITEM_H

#include <string>

class User;

enum class ItemType {
  HealPotion, None
};

class Item {
private:
  std::string name;
  ItemType type = ItemType::None;

public:
  Item();
  Item(std::string name, ItemType item);
  virtual ~Item();

  virtual void Use(User& user) = 0;
  virtual std::string GetName();
  virtual void UsePrint();

  ItemType GetItemType() const;
};

#endif
