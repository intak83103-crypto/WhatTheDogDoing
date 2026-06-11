#include "../include/Item.h"

#include "../include/IO.h"

Item::Item(std::string name) {
  this->name = name;
}

Item::~Item() {}

std::string Item::GetName() {
  return name;
}

void Item::UsePrint() {
  IO::UseItem(name);
}
