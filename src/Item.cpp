#include "../include/Item.h"

#include "../include/IO.h"
#include "../include/User.h" 


Item::Item() {}

Item::Item(std::string name, ItemType type, ItemTargetType target) {
  this->name = name;
  this->type = type;
  this->target = target;
}

Item::~Item() {}

std::string Item::GetName() {
  return name;
}


ItemType Item::GetItemType() const {
  return type;
}

ItemTargetType Item::GetItemTargetType() const {
  return target;
}

const std::string& Item::GetDetail() {
  return detail;
}
void Item::SetDetail(const std::string& detail) {
  this->detail = detail;
}
