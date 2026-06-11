#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "Product.h"

class ProductDD : public Product {
public:
  ProductDD();
  void Apply(User& user) const override;
};

class ProductHealPotion : public Product {
public:
  ProductHealPotion();
  void Apply(User& user) const override;
};

#endif
