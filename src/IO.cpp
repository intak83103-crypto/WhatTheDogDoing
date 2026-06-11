#include "../include/IO.h"

#include <iomanip>
#include <iostream>

#include "../include/DogDoing.h"
#include "../include/Item.h"
#include "../include/Product.h"
#include "../include/User.h"

void IO::PrintDot(int dot) {
  for ( int i = 0; i < dot; i++ ) {
    std::cout << "." << std::endl;;
  }
}

bool IO::GetToken(std::string& token) {
  if ( std::cin >> token ) {
    return true;
  }
  return false;
}

void IO::Divider() {
  std::cout << "-----------------------------------------------------------" << std::endl;
}

void IO::Divider(int n) {
  for ( int i = 0; i < n; i++ ) {
    Divider();
  }
}

void IO::PrintNewUser() {
  PrintDot(9);
  std::cout << "創建新的用戶中..." << std::endl;
  std::cout << "請輸入用戶名 :  " << std::endl;
}

void IO::PrintUserSetUp(const std::string& name, const int& id) {
  PrintDot(7);
  Divider();
  std::cout  << "Hi! " << name << " , User ID : " << id << std::endl;
  Divider();
}

void IO::PrintDDSetUp(const DogDoing& dd) {
  std::cout << "獲得刀盾 : ";
  PrintDDtitle(dd);
  std::cout << std::endl;
}

void IO::FirstDD() {
  std::cout << "獲得第一隻刀盾!!" << std::endl;
}

void IO::PrintDDInfo(const DogDoing& dd) {
  PrintDot(9);
  std::cout << std::fixed << std::setprecision(1);
  std::cout << "當前刀盾：" << std::endl;
  Divider();
  PrintDDtitle(dd);
  std::cout << std::endl;
  Divider();
  std::cout << "  HP  : " << dd.GetHp() << " / " << dd.GetMaxHp() << std::endl;
  std::cout << "  ATK : " << dd.GetATK() << std::endl;
  std::cout << "  MP  : " << dd.GetMp() << " / " << dd.GetMaxMp() << std::endl;
  Divider();
  PrintDot(1);
}

void IO::PrintRank(int rank) {
  if (rank >= 5 ) {
    rank = 5;
  }
  if ( rank <= 1 ) {
    rank = 1;
  }
  for ( int i = 0; i < rank; i++ ) {
    std::cout << "\u2606";
  }
  for ( int i = 0; i < 5 - rank; i++ ) {
    std::cout << " ";
  }
  return;
}

void IO::EditorStart() {
  PrintDot(7);
  Divider();
  std::cout << "\n我的刀盾！ | What The Dog Doing?\n" << std::endl;
  Divider();
}

void IO::PrintOperateWating() {
  Divider();
  PrintDot(3);
  Divider();
  std::cout << "  (請輸入操作...) " << std::endl;
  Divider();
}

void IO::PrintHelpHint() {
  std::cout << std::endl;
  std::cout << "Hint : 隨時輸入 Help / h 列出指令列表" << std::endl;
}

void IO::PrintCinError() {
  std::cout << "讀取失敗" << std::endl;
}

void IO::PrintHelpDD(std::string name) {
  PrintDot(9);
  Divider();
  std::cout << "HELP!" << std::endl;
  Divider();
  std::cout << "L / List  | 列出" << name << "的所有刀盾 " << std::endl;
  std::cout << "D / DD    | 查看當前刀盾數值" << std::endl;
  std::cout << "R / Rn    | 更改目前刀盾名稱" << std::endl;
  std::cout << "B / bp    | 查看" << name << "的背包" << std::endl;
  std::cout << "S / Shop  | 查看商店" << std::endl;
  std::cout << "M / Me    | 查看" << name << "的資訊" << std::endl;
  std::cout << "U / User  | 進入使用者介面" << std::endl;
}

void IO::ListAllDD(User& user) {
  PrintDot(7);
  Divider();
  std::cout << user.GetUserName() << "的刀盾：";
  std::cout << "       (輸入數字可切換至對應刀盾)" << std::endl;
  Divider();
  std::cout << "No.   | Rank  | Level | Name " << std::endl;
  Divider();
  for ( int i = 0; i < user.GetNumOfDD(); i++ ) {
    std::cout << i + 1;
    if ( i == user.GetCurrDDIndex() ) {
      std::cout << "  > ";
    } else {
      std::cout << "    ";
    }
    std::cout << " | ";
    PrintDDtitle(user.GetDD(i));
    std::cout << std::endl;
  }
}

void IO::PrintRenameInfo(std::string name) {
  PrintDot(9);
  std::cout << "更改 " << name << " 的名稱為：" << std::endl;
}

void IO::PrintRenameSuccess(const DogDoing& dd) {
  std::cout << "改名成功" << std::endl;
  PrintDDInfo(dd);
}

void IO::PrintDDtitle(const DogDoing& dd) {
  PrintRank(dd.GetRank());
  std::cout << " | LV." << std::setfill('0') << std::setw(2) 
            << dd.GetLevel() << " | " << dd.GetName();
  std::cout << std::setfill(' ');
}

void IO::PrintInputError(std::string str) {
  PrintDot(9);
  std::cout << "未知指令 : " << str << std::endl;
  PrintHelpHint();
}

void IO::PrintProduct(const Product& product) {
  std::cout << " $"  << std::setw(4)
            << product.GetPrice() << "  | " << product.GetName();
}

void IO::ListProduct(const std::vector<Product*>& products, int coin) {
  std::cout << "持有金幣 : $" << coin << std::endl;
  std::cout << "輸入商品編號購買" << std::endl;
  Divider();
  std::cout << "No. |  Price  | Name "<< std::endl;
  Divider();
  for ( int i = 0; i < products.size(); i++ ) {
    std::cout << i + 1 << "   | " ;
    products[i]->PrintProduct();
    std::cout << std::endl;
  }
}

void IO::PrintHelpShop() {
  PrintDot(9);
  Divider();
  std::cout << "HELP!" << std::endl;
  Divider();
  std::cout << "          | 輸入商品編號購買" << std::endl;
  std::cout << "Q / Quit  | 離開商店" << std::endl;
  std::cout << "L / list  | 列出商店物品" << std::endl; 
}

void IO::PrintQuitShop() {
  PrintDot(9);
  Divider();
  std::cout << "離開商店" << std::endl;
}

void IO::PrintNotEnoughCoin() {
  PrintDot(9);
  std::cout << "coin不足! " << std::endl;
}

void IO::PrintUserInfo(const User& user) {
  PrintDot(9);
  Divider();
  std::cout << user.GetUserName() << std::endl;
  Divider();
  std::cout << "刀盾數量 : " << user.GetNumOfDD() << std::endl;
  std::cout << "持有coin : $" << user.GetCoin() << std::endl;
}

void IO::PrintBuySuccess(const User& user, Product* product) {
  PrintDot(9);
  Divider();
  std::cout << user.GetUserName() << "成功購買 : " << product->GetName() << std::endl;
}

void IO::PrintBuyHelp() {
  PrintDot(9);
  Divider();
  std::cout << "HELP!" << std::endl;
  Divider();
  std::cout << "Y / Yes   | 確認購買" << std::endl;
  std::cout << "N / no    | 取消購買" << std::endl;
}
 
void IO::PrintBuyInfo(Product* product) {
  PrintDot(9);
  Divider();
  std::cout << "確認花費 $" << product->GetPrice()
            << " 購買 " << product->GetName() << " ? ( Y / N )" << std::endl;
}

void IO::PrintBuyCancel() {
  PrintDot(9);
  Divider();
  std::cout << "取消購買" << std::endl;
}

void IO::PrintBuyError() {
  PrintDot(9);
  Divider();
  std::cout << "找不到這個商品" << std::endl;
}

void IO::PrintSwitchDDError() {
  PrintDot(9);
  Divider();
  std::cout << "找不到這個刀盾" << std::endl;
}

void IO::PrintSwitchDDSuccess(DogDoing& dd) {
  PrintDot(9);
  Divider();
  std::cout << "已切換至" << dd.GetName() << std::endl;
}

void IO::PrintShop() {
  PrintDot(9);
  Divider();
  std::cout << "進入商店" << std::endl;
  Divider();
}

void IO::PrintUser() {
  PrintDot(9);
  Divider();
  std::cout << "進入使用者介面" << std::endl;
}

void IO::PrintHelpUser() {
  PrintDot(9);
  Divider();
  std::cout << "HELP!" << std::endl;
  Divider();
  std::cout << "L / List  | 列出所有使用者 " << std::endl;
  std::cout << "R / Rn    | 更改目前使用者名稱" << std::endl;
  std::cout << "M / Me    | 查看當前使用者的資訊" << std::endl;
  std::cout << "N / new   | 建立新的使用者" << std::endl;
  std::cout << "D / Del   | 刪除目前使用者" << std::endl;
  std::cout << "b / back  | 回到刀盾頁面" << std::endl;
}

void IO::PrintSetUserName(std::string name) {
  PrintDot(9);
  Divider();
  std::cout << "更改User : " << name << " 的名稱為 : " << std::endl;
}

void IO::ListAllUser(std::vector<User>& users, int index) {
  int n = users.size();
  PrintDot(9);
  Divider();
  std::cout << "所有的使用者 :        (輸入數字切換使用者)" << std::endl;
  Divider();
  std::cout << "No.  | Name" << std::endl;
  Divider();

  for ( int i = 0; i < n; i++ ) {
    std::cout << i + 1;
    if ( i == index ) {
      std::cout << " >  | ";
    } else {
      std::cout << "    | ";
    }
    std::cout << users[i].GetUserName() << std::endl;
  }
}

void IO::PrintBacktoDD() {
  PrintDot(9);
  Divider();
  std::cout << "已回到刀盾頁面" << std::endl;
}

void IO::PrintConfirmDelUser(std::string name) {
  PrintDot(9);
  Divider();
  std::cout << "確認刪除 " << name << " ? ( Y / N ) "  << std::endl;
}

void IO::PrintDelUser(std::string name) {
  PrintDot(9);
  Divider();
  std::cout << "已刪除 : " << name  <<std::endl;
}

void IO::PrintCancelDelUser(std::string name) {
  PrintDot(9);
  Divider();
  std::cout << "取消刪除 : " << name << std::endl;
}

void IO::PrintDelUserError() {
  PrintDot(9);
  Divider();
  std::cout << "Error : 無法刪除最後一位使用者" << std::endl;
}

void IO::PrintDelUserHelp() {
  PrintDot(9);
  Divider();
  std::cout << "HELP!" << std::endl;
  Divider();
  std::cout << "Y / Yes   | 確認刪除" << std::endl;
  std::cout << "N / no    | 取消刪除" << std::endl;
}

void IO::PrintSwitchUserError() {
  PrintDot(9);
  Divider();
  std::cout << "用戶不存在" << std::endl;
}

void IO::PrintSwitchUser(std::string name) {
  PrintDot(9);
  Divider();
  std::cout << "已切換至 : " << name << std::endl;
}

void IO::PrintBuyDone(std::string name) {
  PrintDot(9);
  Divider();
  std::cout << "已購買 : " << name << std::endl;
}

void IO::ListBackpack(std::string user, const std::vector<Item*>& item) {
  PrintDot(9);
  Divider();
  std::cout << user + "的背包 : " << std::endl;
  Divider();
  int n = item.size();
  if ( n == 0 ) {
    std::cout << "沒有東西..." << std::endl;
  }
  for ( int i = 0; i < n; i ++ ) {
    std::cout << i + 1 << "  | ";
    std::cout << item[i]->GetName() << std::endl;
  }
}

void IO::PrintSwitchBackpack() {
  PrintDot(9);
  Divider();
  std::cout << "已切換至背包" << std::endl;
}

void IO::UseItem(std::string& name) {
  PrintDot(9);
  Divider();
  std::cout << "已使用 : " << name << std::endl;
}

void IO::PrintQuitBack() {
  PrintDot(9);
  Divider();
  std::cout << "已離開背包" << std::endl;
}

void IO::UseItemError() {
  PrintDot(9);
  Divider();
  std::cout << "找不到這個物品" << std::endl;
}

void IO::HelpBackpack() {
  PrintDot(9);
  Divider();
  std::cout << "HELP!" << std::endl;
  Divider();
  std::cout << "L / List  | 列出所有背包物品 " << std::endl;
  std::cout << "          | 輸入數字使用物品" << std::endl;
  std::cout << "b / back  | 回到刀盾頁面" << std::endl;    
}
