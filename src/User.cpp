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
  coin = 5000;
  backpack = {};
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

void User::GetItem(ItemType type) {
  int n = backpack.size();
  for ( int i = 0; i < n; i ++ ) {
    if ( backpack[i].type == type ) {
      backpack[i].count += 1;
      return;
    }
  }
  backpack.push_back({type, 1});
}

void User::ListBackpack(bool divider) {
  std::vector<BackpackInfo> item;
  int n = backpack.size();
  for ( int i = 0; i < n; i++ ) {
    ItemInfo info = ItemDatabase::GetInfo(backpack[i].type);
    item.push_back({info.name, backpack[i].count});
  }
  IO::ListBackpack(name, item, divider);
}

void User::UseItem(int index, int target_dd) {
  int real_index = index - 1;
  if ( real_index < 0 ||
       static_cast<std::size_t>(real_index) >= backpack.size()  ) {
    IO::UseItemError();
    return;
  }
  if ( backpack[real_index].count <= 0 ) {
    DeleteItem(real_index);
    return;
  }
  if ( target_dd != -1 && DogDoingIndexCheck(target_dd - 1) == false ) {
    return;
  }
  ItemDatabase::UseItem(*this, backpack[real_index].type, target_dd);

  backpack[real_index].count -= 1;

  if ( backpack[real_index].count <= 0 ) {
    DeleteItem(real_index);
  }
}
void User::DeleteItem(int index) {
  backpack.erase(backpack.begin() + index);
}
ItemType User::GetItemOfBackpack(int index) {
  index--;
  if ( BackpackIndexCheck(index) ) {
    return backpack[index].type;
  }
  return ItemType::None;
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

DogDoing* User::GetIndexOfDD(int index) {
  int real_index = index - 1;
  if ( DogDoingIndexCheck(real_index) ) {
    return &dogdoings[real_index];
  }
  return nullptr;
}
bool User::BackpackIndexCheck(int index) const {
  int n = backpack.size();
  if ( index < 0 || index >= n ) {
    return false;
  }
  return true;
}

bool User::DogDoingIndexCheck(int index) const {
  int n = dogdoings.size();
  if ( index < 0 || index >= n ) {
    IO::PrintSwitchDDError();
    return false;
  }
  return true;
}
