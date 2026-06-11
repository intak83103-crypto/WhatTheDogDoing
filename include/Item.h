#ifndef ITEM_H
#define ITEM_H

#include <string>

class User;

class Item {
private:
  std::string name;

public:
  Item(std::string name);
  virtual ~Item();

  virtual void Use(User& user) = 0;
  virtual std::string GetName();
  virtual void UsePrint();
};

#endif
