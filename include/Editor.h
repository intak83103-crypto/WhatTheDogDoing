#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include <vector>

#include "Shop.h"
#include "User.h"
#include "DisplayData.h"

enum class Control {
  User, DogDoing, Shop, Buy, None, DelUser, Backpack, SelectTargetDD, EquipSkill
};

enum class Operate {
  None, PrintInfo, ListDD, Quit, HelpDD, HelpUser, RenameDD, Unknown, SwitchDD,
  Backpack, ListBackpack, UseItem, QuitBackpack, HelpBackpack,
  Shop, HelpShop, QuitShop, ListShop, GetUserInfo, Buy,
  HelpBuy, ConfirmBuy, CancelBuy,
  User, AddUser, DelUser, ReNameUser, QuitUser, ListUser, BacktoDD, SwitchUser,
  ConfirmDelUser, CanCelDelUser, ConfirmDel, CanCelDel, HelpDelUser,
  HelpSelectTargetDD, SelectTargetDD, BacktoBackpack,
  BattleTest, Explore, SkillLibrary, EquipSkill, Op
};

class Editor {
private:
  std::vector<User> users;
  Control control = Control::DogDoing;
  int num_of_user = 0;
  int curr_user = -1;
  Shop shop;
  int buy_index = -1;
  int switch_dd_index = -1;
  int switch_user_index = -1;
  int use_item_of_bp = -1;
  int select_dd_index = -1;
  int equip_skill_slot = -1;

  std::vector<std::string> GetUserNameArray() const;
  void NewUser();
  void Start();
  std::string ToLower(std::string str);
  bool IsDigit(std::string str);
  Operate GetOp(std::string op);
  void OperateDogDoing(Operate op, std::string str);
  void OperateShop(Operate op, std::string str);
  bool ConfirmIndex(int index);
  void OperateBuy(Operate op, std::string str);
  void OperateUser(Operate op, std::string str);
  void OperateDelUser(Operate op, std::string str);
  void OperateBackpack(Operate op, std::string str);
  void OperateSelectTargetDD(Operate op, std::string str);
  void OperateEquipSkill(Operate op, std::string str);
  void BattleTest();
  void StartBattleTest(int enemy_index);
  void SetUpShop();
  
public:
  void Run();
};

#endif
