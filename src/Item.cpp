#include "../include/Item.h"

#include "../include/IO.h"



Item::Item(std::string name, ItemType type) {
  this->name = name;
  this->type = type;
}

Item::~Item() {}

std::string Item::GetName() {
  return name;
}

void Item::UsePrint() {
  IO::UseItem(name);
}

ItemType Item::GetItemType() const {
  return type;
}
