#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "Product.h"

class ProductDD : public Product {
public:
  ProductDD();
  void Apply(User& user) const override;
};

class ProductSmallHealPotion : public Product {
public:
  ProductSmallHealPotion();
  void Apply(User& user) const override;
};

class ProductSmallExpPotion : public Product {
public:
  ProductSmallExpPotion();
  void Apply(User& user) const override;
};

#endif
