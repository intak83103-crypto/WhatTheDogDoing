#include "../include/IO.h"

#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <thread>

#include "../include/DogDoing.h"
#include "../include/Item.h"
#include "../include/Product.h"
#include "../include/User.h"


void IO::PrintDot(int dot) {
  for ( int i = 0; i < dot; i++ ) {
    std::cout << "\n" << std::endl;;
  }
}

bool IO::GetToken(std::string& token) {
  if ( std::cin >> token ) {
    return true;
  }
  return false;
}

void IO::Divider() {
  std::cout << "------------------------------------------------------------" << std::endl;
}

void IO::Divider(int n) {
  for ( int i = 0; i < n; i++ ) {
    Divider();
  }
}

void IO::Pause(int seconds) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void IO::PrintNewUser() {
  PrintDot(5);
  std::cout << "創建新的用戶中..." << std::endl;
  std::cout << "請輸入用戶名 :  " << std::endl;
}

void IO::PrintUserSetUp(const std::string& name, const int& id) {
  PrintDot(7);
  Divider();
  std::cout  << "Hi! " << name << " , User ID : " << id << std::endl;
  Divider();
}

void IO::PrintDDSetUp(DDtitleInfo dd) {
  std::cout << "獲得刀盾 : ";
  PrintDDtitle(dd);
  std::cout << std::endl;
}

void IO::FirstDD() {
  std::cout << "獲得第一隻刀盾!!" << std::endl;
}

void IO::PrintDDInfo(DDInfo info) {
  CreatureInfo dd = info.property;
  PrintDot(9);
  std::cout << std::fixed << std::setprecision(1);
  std::cout << "當前刀盾：" << std::endl;
  Divider();
  PrintDDtitle(info.title);
  std::cout << std::endl;
  Divider();
  std::cout << "  血量    : " << dd.hp << " / " << dd.max_hp << std::endl;
  std::cout << "  攻擊    : " << dd.attack << std::endl;
  std::cout << "  速度    : " << dd.speed << std::endl;
  std::cout << "  技能數量: " << info.property.num_of_skill << std::endl;
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

void IO::ListAllDD(std::vector<DDtitleInfo> dd, std::string name, int index) {
  PrintDot(7);
  Divider();
  int n = dd.size();
  std::cout << name << "的刀盾：";
  std::cout << "       (輸入數字可切換至對應刀盾)" << std::endl;
  Divider();
  std::cout << "No.   | Rank  | Element | Level | Name " << std::endl;
  Divider();
  for ( int i = 0; i < n; i++ ) {
    std::cout << i + 1;
    if ( i == index ) {
      std::cout << "  > ";
    } else {
      std::cout << "    ";
    }
    std::cout << " | ";
    PrintDDtitle(dd[i]);
    std::cout << std::endl;
  }
}

void IO::PrintRenameInfo(std::string name) {
  PrintDot(9);
  std::cout << "更改 " << name << " 的名稱為：" << std::endl;
}

void IO::PrintRenameSuccess(DDInfo dd) {
  std::cout << "改名成功" << std::endl;
  PrintDDInfo(dd);
}

void IO::PrintDDtitle(DDtitleInfo title) {
  PrintRank(title.rank);
  Element element = title.element;
  if ( element == Element::None ) {
    std::cout << " | 無屬性 ";
  } else if ( element == Element::Fire ) {
    std::cout << " |   火   ";
  } else if ( element == Element::Grass ) {
    std::cout << " |   草   ";
  } else if ( element == Element::Thunder ) {
    std::cout << " |   雷   ";
  } else if ( element == Element::Water ) {
    std::cout << " |   水   ";
  } else if ( element == Element::Dark ) {
    std::cout << " |   暗   ";
  }

  std::cout << " | LV." << std::setfill('0') << std::setw(2) 
            << title.level << " | " << title.name;
  std::cout << std::setfill(' ');
}

void IO::PrintInputError(std::string str) {
  PrintDot(9);
  std::cout << "未知指令 : " << str << std::endl;
  PrintHelpHint();
}

void IO::PrintProduct(ProductInfo pd) {
  std::cout << " $"  << std::setw(4)
            << pd.price << "  | " << pd.name;
}

void IO::ListProduct(const std::vector<ProductInfo>& products, int coin) {
  std::cout << "持有金幣 : $" << coin << std::endl;
  std::cout << "輸入商品編號購買" << std::endl;
  Divider();
  std::cout << "No. |  Price  | Name "<< std::endl;
  Divider();
  int n = products.size();
  for ( int i = 0; i < n; i++ ) {
    std::cout << i + 1 << "   | " ;
    PrintProduct(products[i]);
    std::cout << std::endl;
  }
}

void IO::PrintHelpShop() {
  PrintDot(9);
  Divider();
  std::cout << "HELP!" << std::endl;
  Divider();
  std::cout << "          | 輸入商品編號購買" << std::endl;
  std::cout << "b / Back  | 離開商店" << std::endl;
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

void IO::PrintUserInfo(UserInfo user) {
  PrintDot(9);
  Divider();
  std::cout << user.name << std::endl;
  Divider();
  std::cout << "刀盾數量 : " << user.num_of_dd << std::endl;
  std::cout << "持有coin : $" << user.coin << std::endl;
}

void IO::PrintBuySuccess(std::string name, ProductInfo product) {
  PrintDot(9);
  Divider();
  std::cout << name << "成功購買 : " << product.name << std::endl;
}

void IO::PrintBuyHelp() {
  PrintDot(9);
  Divider();
  std::cout << "HELP!" << std::endl;
  Divider();
  std::cout << "Y / Yes   | 確認購買" << std::endl;
  std::cout << "N / no    | 取消購買" << std::endl;
}
 
void IO::PrintBuyInfo(ProductInfo product) {
  PrintDot(9);
  Divider();
  std::cout << "確認花費 $" << product.price
            << " 購買 " << product.name << " ? ( Y / N )" << std::endl;
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

void IO::PrintSwitchDDSuccess(std::string name) {
  PrintDot(9);
  Divider();
  std::cout << "已切換至" << name << std::endl;
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

void IO::ListAllUser(std::vector<std::string> users, int index) {
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
    std::cout << users[i] << std::endl;
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

void IO::ListBackpack(std::string user, std::vector<BackpackInfo>& backpack, bool divider) {
  if ( divider ) {
    PrintDot(9);
    Divider();
  }
  std::cout << user + "的背包 : " << std::endl;
  Divider();
  int n = backpack.size();
  if ( n == 0 ) {
    std::cout << "沒有東西..." << std::endl;
    return;
  }
  for ( int i = 0; i < n; i ++ ) {
    std::cout << i + 1 << "  | ";
    std::cout << backpack[i].name << " x" << backpack[i].count << std::endl;
  }
}

void IO::PrintSwitchBackpack() {
  PrintDot(9);
  Divider();
  std::cout << "已切換至背包" << std::endl;
}

void IO::UseItem(std::string name) {
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

void IO::HealSuccess(std::string name, int hp) {
  std::cout << std::endl;
  std::cout << name << " 目前血量  : " << hp << std::endl;
}

void IO::PrintSelectDD(std::vector<DDtitleInfo> dd, std::string item) {
  PrintDot(9);
  Divider();
  std::cout << "選擇你要使用 " << item << " 的刀盾： " << std::endl;
  Divider();
  std::cout << "No.   | Rank  | Level | Name " << std::endl;
  Divider();
  int n = dd.size();
  for ( int i = 0; i < n; i++ ) {
    std::cout << i + 1;
    std::cout << "    ";
    std::cout << " | ";
    PrintDDtitle(dd[i]);
    std::cout << std::endl;
  }


}

void IO::HelpSelecttargetDD() {
  PrintDot(9);
  Divider();
  std::cout << "HELP!" << std::endl;
  Divider();
  std::cout << "          | 輸入刀盾編號使用物品" << std::endl;
  std::cout << "b / Back  | 取消使用" << std::endl;
}

void IO::PrintBackToBackpack() {
  PrintDot(9);
  Divider();
  std::cout << "取消使用" << std::endl;
  std::cout << std::endl;
}

void IO::PrintSkillSelectError() {
  PrintDot(9);
  Divider();
  std::cout << "沒有這個技能" << std::endl;
}

void IO::PrintBattleDoesNotHit() {
  std::cout << "  > 未命中..." << std::endl;
  Divider();
}

void IO::PrintBattleDamage(std::string attacker, std::string defender, int damage) {
  std::cout << "  > " + attacker + "對" + defender + "造成 " << damage << "點傷害" << std::endl;
  Divider();
}

void IO::PrintBattleTurnStart(int i) {
  PrintDot(2);
  Divider();
  std::cout << "第" << i << "回合" << std::endl;
  Divider();
  Pause(1);
}

void IO::PrintBattleCrit() {
  std::cout << "  >        暴擊！    " << std::endl;
}

void IO::PrintUseSkill(std::string name, std::string skill_name) {
  PrintDot(2);
  Divider();
  std::cout << "  > " +name + "發動了：" + skill_name << std::endl;
  Divider();
}

void IO::PrintBattleRoundStart(std::string name) {
  PrintDot(2);
  std::cout << name + "的攻擊" << std::endl;
}

void IO::PrintBattleStart(std::string user, std::string enemy, int is_advantage) {
  PrintDot(9);
  Divider();
  std::cout << "戰鬥開始 !" << std::endl;
  std::cout << std::endl;
  std::cout << user + " 對決 " + enemy + "  ";
  if ( is_advantage == 1 ) {
    std::cout << "( 屬性克制 ! )";
  } else if ( is_advantage == 2 ) {
    std::cout << "( 屬性被克制 ! )";
  }
  std::cout << std::endl;
  PrintDot(3);
}
void IO::PrintBattleEnd() {
  PrintDot(3);
  Divider();
  std::cout << "戰鬥結束" << std::endl; 
}
void IO::PrintBattleDDDie(std::string dd_name) {
  PrintDot(9);
  Divider();
  std::cout << dd_name + "已死亡..." << std::endl;
}
void IO::PrintBattleWin() {
  Divider();
  std::cout << "戰鬥勝利 !" << std::endl;
}
void IO::PrintBattleLose() {
  Divider();
  std::cout << "戰鬥失敗..." << std::endl;
}

void IO::FullOfSkill() {
  PrintDot(9);
  Divider();
  std::cout << "技能已滿" << std::endl;
}

void IO::PrintNormalAttackError() {
  PrintDot(9);
  Divider();
  std::cout << "不可替換普通攻擊" << std::endl;
}

void IO::PrintDots() {
  PrintDot(1);
  std::cout << "      ...     "  << std::endl;
  PrintDot(1);
}

void IO::PrintSkillUnready() {
  PrintDot(2);
  std::cout << "技能冷卻中..." << std::endl;
  PrintDot(2);
}

void IO::PrintBattleHeal(std::string attacker, int heal) {
  std::cout << "  > " + attacker + "回復了  : " << heal << "點血量" << std::endl;
  Divider();
}

void IO::PrintBattleHpInfo(CreatureInfo info) {
  std::cout << "   " + info.name + " : " << info.hp << " / " << info.max_hp <<  std::endl;
}
