#include "../include/Product.h"

#include "../include/IO.h"

Product::Product() {}

Product::Product(std::string name, int price) {
  this->price = price;
  this->name = name;
}

Product::~Product() {}

std::string Product::GetName() const {
  return name;
}

int Product::GetPrice() const {
  return price;
}

void Product::PrintProduct() {
  IO::PrintProduct(*this);
}
