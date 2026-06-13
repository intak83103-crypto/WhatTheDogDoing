#ifndef IO_H
#define IO_H

#include <string>
#include <vector>
#include "DisplayData.h"

class IO {
public:

  static void PrintDot(int dot);
  static bool GetToken(std::string& token);
  static void Divider();
  static void Divider(int n);
  static void PrintNewUser();
  static void PrintUserSetUp(const std::string& name, const int& id);
  static void PrintDDSetUp(DDtitleInfo dd);
  static void FirstDD();
  static void PrintDDInfo(DDInfo dd);
  static void PrintRank(int rank);
  static void EditorStart();
  static void PrintOperateWating();
  static void PrintHelpHint();
  static void PrintCinError();
  static void PrintHelpDD(std::string name);
  static void ListAllDD(std::vector<DDtitleInfo> dd, std::string name, int index);
  static void PrintRenameInfo(std::string name);
  static void PrintRenameSuccess(DDInfo dd);
  static void PrintDDtitle(DDtitleInfo title);
  static void PrintInputError(std::string str);
  static void PrintProduct(ProductInfo pd);
  static void ListProduct(const std::vector<ProductInfo>& products, int coin);
  static void PrintHelpShop();
  static void PrintQuitShop();
  static void PrintNotEnoughCoin();
  static void PrintUserInfo(UserInfo user);
  static void PrintBuySuccess(std::string name, ProductInfo product);
  static void PrintBuyHelp();
  static void PrintBuyInfo(ProductInfo product);
  static void PrintBuyCancel();
  static void PrintBuyError();
  static void PrintSwitchDDError();
  static void PrintSwitchDDSuccess(std::string name);
  static void PrintShop();
  static void PrintUser();
  static void PrintHelpUser();
  static void PrintSetUserName(std::string name);
  static void ListAllUser(std::vector<std::string> users, int index);
  static void PrintBacktoDD();
  static void PrintConfirmDelUser(std::string name);
  static void PrintDelUser(std::string name);
  static void PrintCancelDelUser(std::string name);
  static void PrintDelUserError();
  static void PrintDelUserHelp();
  static void PrintSwitchUserError();
  static void PrintSwitchUser(std::string name);
  static void PrintBuyDone(std::string name);
  static void ListBackpack(std::string user, std::vector<BackpackInfo>& backpack, bool divider = false);
  static void PrintSwitchBackpack();
  static void UseItem(std::string name);
  static void PrintQuitBack();
  static void UseItemError();
  static void HelpBackpack();
  static void HealSuccess(std::string name, int hp);
  static void PrintSelectDD(std::vector<DDtitleInfo> dd, std::string item);
  static void HelpSelecttargetDD();
  static void PrintBackToBackpack();
  static void PrintSkillSelectError();
  static void PrintBattleDoesNotHit();
  static void PrintBattleDamage(std::string attacker, std::string defender, int damage);
  static void PrintBattleTurnStart(int i);
  static void PrintBattleCrit();
  static void PrintUseSkill(std::string name, std::string skill_name);
  static void PrintBattleRoundStart(std::string name);
  static void PrintBattleStart(std::string user, std::string enemy);
  static void PrintBattleEnd();
  static void PrintBattleDDDie(std::string dd_name);
  static void PrintBattleWin();
  static void PrintBattleLose();
};

#endif
