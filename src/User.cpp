#include "../include/User.h"

#include <cstddef>

#include "../include/IO.h"

User::User() {}

User::User(std::string name, int id) {
  this->name = name;
  this->id = id;
  id_of_dd = 1;
  IO::PrintUserSetUp(name,id);
  std::string dd_name;
  IO::FirstDD();
  dogdoings.emplace_back(DogDoing(id_of_dd++));
  curr_dd = 0;
  coin = 200;
  backpack = {};
}

User::~User() {
  int n = backpack.size();
  for ( int i = 0; i < n; i++ ) {
    delete backpack[i].item;
  }
}

int User::GetNumOfDD() const {
  return dogdoings.size();
}

DogDoing& User::GetCurrentDD() {
  return dogdoings[curr_dd];
}

int User::GetCurrDDIndex() const {
  return curr_dd;
}

std::string User::GetUserName() const {
  return name;
}

void User::SetName() {
  std::string str;
  IO::PrintSetUserName(name);
  IO::GetToken(str);
  name = str;
  PrintInfo();
}

DogDoing& User::GetDD(int index) {
  return dogdoings[index];
}

void User::AddDD() {
  dogdoings.emplace_back(DogDoing(id_of_dd++));
  curr_dd = dogdoings.size() - 1;
}

int User::GetCoin() const {
  return coin;
}

void User::AddCoin(int coins) {
  coin += coins;
}

bool User::PayCoin(int price) {
  if ( price > coin ) {
    IO::PrintNotEnoughCoin();
    return false;
  }
  coin -= price;
  return true;
}

void User::PrintInfo() const {
  IO::PrintUserInfo({name, GetNumOfDD(), coin});
}

void User::SwitchDD(int index) {
  if ( index <= 0 || static_cast<std::size_t>(index) > dogdoings.size() ) {
    IO::PrintSwitchDDError();
    return;
  }
  curr_dd = index - 1;
  IO::PrintSwitchDDSuccess(dogdoings[curr_dd].GetName());
}

void User::GetItem(Item* item) {
  int n = backpack.size();
  for ( int i = 0; i < n; i ++ ) {
    if ( backpack[i].item->GetItemType() == item->GetItemType() ) {
      backpack[i].count += 1;
      delete item;
      return;
    }
  }
  backpack.push_back({item, 1});
}

void User::ListBackpack() {
  std::vector<BackpackInfo> item;
  int n = backpack.size();
  for ( int i = 0; i < n; i++ ) {
    item.push_back({backpack[i].item->GetName(), backpack[i].count});
  }
  IO::ListBackpack(name, item);
}

void User::UseItem(int index) {
  int real_index = index - 1;
  if ( real_index < 0 ||
       static_cast<std::size_t>(real_index) >= backpack.size()  ) {
    IO::UseItemError();
    return;
  }
  if ( backpack[real_index].count > 0 ) {
    backpack[real_index].item->Use(*this);
    backpack[real_index].count -= 1;
  }
  if ( backpack[real_index].count <= 0 ) {
    DeleteItem(real_index);
  }
}
void User::DeleteItem(int index) {
  delete backpack[index].item;
  backpack.erase(backpack.begin() + index);
}
Item* User::GetItemOfBackpack(int index) {
  int real_index = index - 1;
  if ( real_index < 0 ||
       static_cast<std::size_t>(real_index) >= backpack.size()  ) {
    IO::UseItemError();
    return nullptr;
  }
  return backpack[real_index].item;
}

void User::ListAllDD() const {
  IO::ListAllDD(GetAllDDtitleInfo(), name, curr_dd);
}

std::vector<DDtitleInfo> User::GetAllDDtitleInfo() const {
  std::vector<DDtitleInfo> ddstitle;
  for ( DogDoing dd : dogdoings ) {
    ddstitle.push_back(dd.TitlePackage());
  }
  return ddstitle;
}