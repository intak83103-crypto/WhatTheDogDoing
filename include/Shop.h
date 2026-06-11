#ifndef SHOP_H
#define SHOP_H

#include <vector>

#include "Product.h"

class User;

class Shop {
private:
  std::vector<Product*> products;

public:
  void ListProduct(int coin);
  void AddProduct(Product* p);
  ~Shop();

  void Buy(int index, User& user);
  Product* GetProduct(int index);
  int GetNumOfProduct();
};

#endif
