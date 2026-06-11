#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#include "DogDoing.h"
#include "Item.h"

class User {
private:
  struct BackpackSlot{
    Item* item;
    int count;
  };
  std::string name;
  int id;
  int curr_dd = -1;
  std::vector<DogDoing> dogdoings;
  int coin;
  int id_of_dd;
  std::vector<BackpackSlot> backpack;

public:
  User();
  explicit User(std::string name, int id);
  ~User();

  int GetNumOfDD() const;
  DogDoing& GetCurrentDD();
  int GetCurrDDIndex() const;
  std::string GetUserName() const;
  void SetName();
  DogDoing& GetDD(int index);
  void AddDD();
  int GetCoin() const;
  void AddCoin(int coins);
  bool PayCoin(int price);
  void PrintInfo() const;
  void SwitchDD(int index);
  void GetItem(Item* item);
  void ListBackpack();
  void DeleteItem(int index);
  void UseItem(int index);
  Item* GetItemOfBackpack(int index);
  void ListAllDD() const;
  std::vector<DDtitleInfo> GetAllDDtitleInfo() const;
};

#endif
