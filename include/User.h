#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#include "DogDoing.h"
#include "Item.h"
#include "skill.h"

class User {
private:
  struct BackpackSlot{
    ItemType type;
    int count;
  };
  std::vector<SkillID> skill_list;
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

  int GetNumOfDD() const;
  DogDoing& GetCurrentDD();
  int GetCurrDDIndex() const;
  std::string GetUserName() const;
  DogDoing* GetIndexOfDD(int index);
  void SetName();
  DogDoing& GetDD(int index);
  void AddDD();
  int GetCoin() const;
  void AddCoin(int coins);
  bool PayCoin(int price);
  void PrintInfo() const;
  void SwitchDD(int index);
  void GetItem(ItemType type);
  void ListBackpack(bool divider = true);
  void DeleteItem(int index);
  void UseItem(int index, int target_dd = -1);
  ItemType GetItemOfBackpack(int index);
  void ListAllDD() const;
  bool BackpackIndexCheck(int index) const;
  bool DogDoingIndexCheck(int index) const;
  std::vector<DDtitleInfo> GetAllDDtitleInfo() const;
};

#endif
