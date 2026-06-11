#include "../include/Shop.h"

#include <cstddef>

#include "../include/IO.h"
#include "../include/User.h"

void Shop::ListProduct(int coin) {
  IO::ListProduct(GetAllProDuctInfo(), coin);
}

void Shop::AddProduct(Product* p) {
  products.push_back(p);
}

Shop::~Shop() {
  int n = products.size();
  for ( int i = 0; i < n; i++ ) {
    delete products[i];
  }
}

void Shop::Buy(int index, User& user) {
  if ( index <= 0 || static_cast<std::size_t>(index) > products.size() ) {
    IO::PrintBuyError();
    return;
  }

  Product* product = products[index - 1];

  if ( user.PayCoin(product->GetPrice()) ) {
    IO::PrintBuyDone(product->GetName());
    product->Apply(user);
  }
}

Product* Shop::GetProduct(int index) {
  return products[index - 1];
}

int Shop::GetNumOfProduct() {
  return products.size();
}

std::vector<ProductInfo> Shop::GetAllProDuctInfo() const {
  std::vector<ProductInfo> infos;
  for ( Product* p : products ) {
    infos.push_back(p->InfoPackage());
  }
  return infos;
}