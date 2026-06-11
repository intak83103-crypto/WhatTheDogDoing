#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include "DisplayData.h"

class User;

class Product {
private:
  int price;
  std::string name;

public:
  Product();
  Product(std::string name, int price);
  virtual ~Product();

  virtual void Apply(User& user) const = 0;

  std::string GetName() const;
  int GetPrice() const;
  void PrintProduct();
  ProductInfo InfoPackage() const;
};

#endif
