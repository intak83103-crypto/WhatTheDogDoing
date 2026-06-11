#ifndef IO_H
#define IO_H

#include <string>
#include <vector>

class DogDoing;
class Item;
class Product;
class User;

class IO {
public:
  static void PrintDot(int dot);
  static bool GetToken(std::string& token);
  static void Divider();
  static void Divider(int n);
  static void PrintNewUser();
  static void PrintUserSetUp(const std::string& name, const int& id);
  static void PrintDDSetUp(const DogDoing& dd);
  static void FirstDD();
  static void PrintDDInfo(const DogDoing& dd);
  static void PrintRank(int rank);
  static void EditorStart();
  static void PrintOperateWating();
  static void PrintHelpHint();
  static void PrintCinError();
  static void PrintHelpDD(std::string name);
  static void ListAllDD(User& user);
  static void PrintRenameInfo(std::string name);
  static void PrintRenameSuccess(const DogDoing& dd);
  static void PrintDDtitle(const DogDoing& dd);
  static void PrintInputError(std::string str);
  static void PrintProduct(const Product& product);
  static void ListProduct(const std::vector<Product*>& products, int coin);
  static void PrintHelpShop();
  static void PrintQuitShop();
  static void PrintNotEnoughCoin();
  static void PrintUserInfo(const User& user);
  static void PrintBuySuccess(const User& user, Product* product);
  static void PrintBuyHelp();
  static void PrintBuyInfo(Product* product);
  static void PrintBuyCancel();
  static void PrintBuyError();
  static void PrintSwitchDDError();
  static void PrintSwitchDDSuccess(DogDoing& dd);
  static void PrintShop();
  static void PrintUser();
  static void PrintHelpUser();
  static void PrintSetUserName(std::string name);
  static void ListAllUser(std::vector<User>& users, int index);
  static void PrintBacktoDD();
  static void PrintConfirmDelUser(std::string name);
  static void PrintDelUser(std::string name);
  static void PrintCancelDelUser(std::string name);
  static void PrintDelUserError();
  static void PrintDelUserHelp();
  static void PrintSwitchUserError();
  static void PrintSwitchUser(std::string name);
  static void PrintBuyDone(std::string name);
  static void ListBackpack(std::string user, const std::vector<Item*>& item);
  static void PrintSwitchBackpack();
  static void UseItem(std::string& name);
  static void PrintQuitBack();
  static void UseItemError();
  static void HelpBackpack();
};

#endif
