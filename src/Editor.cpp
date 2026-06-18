#include "../include/Editor.h"

#include <cctype>
#include <cstddef>
#include <memory>

#include "../include/IO.h"
#include "../include/Products.h"
#include "../include/Item.h"
#include "../include/Battle.h"
#include "../include/Enemy.h"

void Editor::NewUser() {
  std::string user_name;
  IO::PrintNewUser();
  IO::GetToken(user_name);
  num_of_user += 1;
  users.emplace_back(user_name, num_of_user);
  curr_user = users.size() - 1;
}

void Editor::Start() {
  IO::EditorStart();
}

// 將玩家輸入統一轉成小寫，讓 Help / help / HELP 都能吃到。
std::string Editor::ToLower(std::string str ) {
  for ( char& c : str ) {
    c = tolower(c);
  }
  return str;
}

// 判斷輸入是否是純數字，數字在不同介面會代表不同選項。
bool Editor::IsDigit(std::string str) {
  for (char& c : str ) {
    if ( !isdigit(c) )
      return false;
  }
  return true;
}

// 依照目前所在介面，把玩家輸入轉換成對應操作。
// 這裡只負責判斷指令，真正執行會交給 OperateXXX 函式。
Operate Editor::GetOp(std::string op) {
  op = ToLower(op);
  if ( control == Control::DogDoing ) {
    // 刀盾主介面：查看刀盾、背包、商店、探索、裝備技能都從這裡進入。
    if ( op == "help" || op == "h" ) {
      return Operate::HelpDD;
    } 
    if ( op == "q" || op == "quit" ) {
      return Operate::Quit;
    }
    if ( op == "l" || op == "list" ) {
      return Operate::ListDD;
    } 
    if ( op == "d" || op == "dd" ) {
      return Operate::PrintInfo;
    }
    if ( op == "r" || op == "rn" ) {
      return Operate::RenameDD;
    }
    if ( op == "s" || op == "shop" ) {
      return Operate::Shop;
    }
    if ( op == "m" || op == "me" ) {
      return Operate::GetUserInfo;
    }
    if ( IsDigit(op) ) {
      switch_dd_index = std::stoi(op);
      return Operate::SwitchDD;
    }
    if ( op == "u" || op == "user" ) {
      return Operate::User;
    }
    if ( op == "b" || op == "bp" ) {
      return Operate::Backpack;
    }
    if ( op == "x" || op == "explore" ) {
      return Operate::Explore;
    }
    if ( op == "k" || op == "skill" || op == "skills" ) {
      return Operate::SkillLibrary;
    }
    if ( op == "op" ) {
      return Operate::Op;
    }
    if ( op == "eq1" || op == "eq2" || op == "eq3" || op == "eq4" ) {
      equip_skill_slot = op[2] - '0';
      return Operate::EquipSkill;
    }

  } else if ( control == Control::User ) {
    // 使用者介面：新增、刪除、切換、重新命名玩家。
    if ( op == "help" || op == "h" ) {
      return Operate::HelpUser;
    }
    if ( op == "r" || op == "rn" ) {
      return Operate::ReNameUser;
    } 
    if ( op == "l" || op == "list" ) {
      return Operate::ListUser;
    } 
    if ( op == "b" || op == "back" ) {
      return Operate::BacktoDD;
    } 
    if ( op == "n" || op == "new" ) {
      return Operate::AddUser;
    }
    if ( op == "d" || op == "del" ) {
      return Operate::DelUser;
    }
    if ( IsDigit(op) ) {
      switch_user_index = std::stoi(op);
      return Operate::SwitchUser;
    }

    

  } else if ( control == Control::Shop ) {
    // 商店介面：數字代表商品編號，買之前會先進入確認頁。
    if ( op == "help" || op == "h" ) {
      return Operate::HelpShop;
    } 
    if ( IsDigit(op) ) {
      buy_index = std::stoi(op);
      return Operate::Buy;
    }
    if ( op == "b" || op == "back" ) {
      return Operate::QuitShop;
    } 
    if ( op == "l" || op == "list" ) {
      return Operate::ListShop;
    } 


  } else if ( control == Control::Buy ) {
    // 購買確認介面：只處理確認、取消、說明。
    if ( op == "y" || op == "yes" ) {
      return Operate::ConfirmBuy;
    }
    if ( op == "h" || op == "help" ) {
      return Operate::HelpBuy;
    }
    if ( op == "n" || op == "no" ) {
      return Operate::CancelBuy;

    }
  } else if ( control == Control::DelUser ) {
    // 刪除使用者確認介面：避免輸入 del 後立刻刪掉。
    if ( op == "h" || op == "help" ) {
      return Operate::HelpDelUser;
    } 
    if ( op == "y" || op == "yes" ) {
      return Operate::ConfirmDelUser;
    }
    if ( op == "n" || op == "no" ) {
      return Operate::CanCelDelUser;
    }
  } else if ( control == Control::Backpack ) {
    // 背包介面：數字代表使用道具，技能庫只查看不放進背包。
    if ( op == "h" || op == "help" ) {
      return Operate::HelpBackpack;
    }
    if ( op == "b" || op == "back" ) {
      return Operate::QuitBackpack;
    }
    if ( op == "l" || op == "list" ) {
      return Operate::ListBackpack;
    }
    if ( op == "k" || op == "skill" || op == "skills" ) {
      return Operate::SkillLibrary;
    }
    if ( IsDigit(op) ) {
      use_item_of_bp = std::stoi(op);
      return Operate::UseItem;
    }
  } else if ( control == Control::SelectTargetDD ) {
    // 道具需要指定刀盾時，數字代表目標刀盾。
    if ( op == "h" || op == "help" ) {
      return Operate::HelpSelectTargetDD;
    } else if ( IsDigit(op) ) {
      select_dd_index = std::stoi(op);
      return Operate::SelectTargetDD;
    } else if ( op == "b" || op == "back" ) {
      return Operate::BacktoBackpack;
    }
  } else if ( control == Control::EquipSkill ) {
    // 裝備技能介面：數字代表技能庫裡的技能編號。
    if ( op == "b" || op == "back" ) {
      return Operate::BacktoDD;
    }
    if ( op == "k" || op == "skill" || op == "skills" ||
         op == "l" || op == "list" ) {
      return Operate::SkillLibrary;
    }
    if ( IsDigit(op) ) {
      return Operate::EquipSkill;
    }
  }
  return Operate::Unknown;
}

// 執行刀盾主介面的操作，是整個遊戲流程的主要入口。
void Editor::OperateDogDoing(Operate op, std::string str) {
  User& user = users[curr_user];
  if ( op == Operate::Quit ) {
    return;
  } else if ( op == Operate::HelpDD ) {
    IO::PrintHelpDD(user.GetUserName());
  } else if ( op == Operate::Unknown ) {
    IO::PrintInputError(str);
  } else if ( op == Operate::PrintInfo ) {
    user.GetCurrentDD().PrintInfo();
  } else if ( op == Operate::ListDD ) {
    user.ListAllDD();
  } else if ( op == Operate::RenameDD ) {
    // 重新命名會額外讀一次輸入，直到成功讀到新名字。
    IO::PrintRenameInfo(user.GetCurrentDD().GetName());
    std::string name;
    while ( IO::GetToken(name) == false ) {
      IO::PrintCinError();
      IO::PrintRenameInfo(user.GetCurrentDD().GetName());
    }
    user.GetCurrentDD().SetName(name);
  } else if ( op == Operate::GetUserInfo ) {
    user.PrintInfo();
  } else if ( op == Operate::SwitchDD ) {
    user.SwitchDD(switch_dd_index);
    switch_dd_index = -1;
  } else if ( op == Operate::Shop ) {
    // 切到商店介面，並立刻列出商品。
    control = Control::Shop;
    IO::PrintShop();
    shop.ListProduct(user.GetCoin());
  } else if ( op == Operate::User ) {
    // 切到使用者管理介面，顯示目前所有使用者。
    control = Control::User;
    IO::PrintUser();
    std::vector<std::string> users_name;
    for ( int i = 0; i < num_of_user; i++ ) {
      users_name.push_back(users[i].GetUserName());
    }
    IO::ListAllUser(users_name, curr_user);
  } else if ( op == Operate::Backpack ) {
    // 切到背包介面，背包裡只放道具，技能庫另外顯示。
    control = Control::Backpack;
    IO::PrintSwitchBackpack();
    user.ListBackpack(false);
  } else if ( op == Operate::Explore ) {
    // 探索會進入怪物選單，選完怪物後才開始戰鬥。
    BattleTest();
  } else if ( op == Operate::SkillLibrary ) {
    user.ListSkillLibrary();
  } else if ( op == Operate::EquipSkill ) {
    // eq1~eq4 先記住要換哪一格，再進入技能選擇介面。
    control = Control::EquipSkill;
    IO::PrintEquipSkillPrompt(equip_skill_slot);
    user.ListSkillLibrary();
  } else if ( op == Operate::Op ) {
    // 教師快速測試：直接給錢、所有技能和全屬性刀盾。
    user.AddCoin(10000);
    user.GrantAllSkills();
    user.GrantAllElementDogDoings();
    IO::PrintOpDone();
  } else if ( op == Operate::BattleTest ) {
    BattleTest();
  }
  
  else {
    IO::PrintCinError();
  }
}

// 執行商店介面的操作，買商品前會先切到購買確認狀態。
void Editor::OperateShop(Operate op, std::string str) {
  User& user = users[curr_user];
  int coin = user.GetCoin();
  if ( op == Operate::Shop ) {
    shop.ListProduct(coin);
  } else if ( op == Operate::HelpShop ) {
    IO::PrintHelpShop();
  } else if ( op == Operate::QuitShop ) {
    control = Control::DogDoing;
    IO::PrintQuitShop();
  } else if ( op == Operate::Unknown ) {
    IO::PrintInputError(str);
  } else if ( op == Operate::ListShop ) {
    IO::PrintDot(9);
    shop.ListProduct(coin);
  } else if ( op == Operate::Buy ) {
    // 數字是商品編號；合法才顯示確認購買。
    int product = std::stoi(str);
    if ( ConfirmIndex(product) == false ) {
      IO::PrintBuyError();
    } else {
      IO::PrintBuyInfo(shop.GetProduct(product)->InfoPackage());
      control = Control::Buy;
    }
  }
}

// 確認商品編號是否存在。
bool Editor::ConfirmIndex(int index) {
  if ( index <= 0 || index > shop.GetNumOfProduct() ) {
    return false;
  }
  return true;
}

// 購買確認頁：按 yes 才真的扣錢並套用商品效果。
void Editor::OperateBuy(Operate op, std::string str ) {
  User& user = users[curr_user];
  if ( op == Operate::HelpBuy) {
    IO::PrintBuyHelp();
  } else if ( op == Operate::ConfirmBuy ) {
    shop.Buy(buy_index, user);
    control = Control::Shop;
    buy_index = -1;
    shop.ListProduct(user.GetCoin());
  } else if ( op == Operate::CancelBuy ) {
    IO::PrintBuyCancel();
    control = Control::Shop;
    buy_index = -1;
    shop.ListProduct(user.GetCoin());
  } else if ( op == Operate::Unknown ) {
    IO::PrintInputError(str);
  }
}

// 使用者管理介面：管理玩家資料，不處理刀盾或戰鬥。
void Editor::OperateUser(Operate op, std::string str) {
  User& user = users[curr_user];
  if ( op == Operate::HelpUser ) {
    IO::PrintHelpUser();
  } else if ( op == Operate::ReNameUser ) {
    user.SetName();
  } else if ( op == Operate::Unknown ) {
    IO::PrintInputError(str);
  } else if ( op == Operate::ListUser ) {
    IO::ListAllUser(GetUserNameArray(), curr_user);
  } else if ( op == Operate::BacktoDD ) {
    IO::PrintBacktoDD();
    control = Control::DogDoing;
  } else if ( op == Operate::AddUser ) {
    NewUser();
    control = Control::DogDoing;
  } else if ( op == Operate::DelUser ) {
    std::string str = user.GetUserName();
    IO::PrintConfirmDelUser(str);
    control = Control::DelUser;
  } else if ( op == Operate::SwitchUser ) {
    // 切換使用者前先檢查編號，避免 vector 越界。
    if ( switch_user_index - 1 < 0 ||
         static_cast<std::size_t>(switch_user_index - 1) >= users.size() ) {
      IO::PrintSwitchUserError();
      switch_user_index = -1;
      return;
    }
    curr_user = switch_user_index - 1;
    switch_user_index = -1;
    IO::PrintSwitchUser(users[curr_user].GetUserName());
    control = Control::DogDoing;
  }
}

// 刪除使用者確認頁，至少要保留一位使用者。
void Editor::OperateDelUser(Operate op, std::string str) {
  User& user = users[curr_user];
  std::string user_name = user.GetUserName();
  if ( op == Operate::HelpDelUser ) {
    IO::PrintDelUserHelp();
  } else if ( op == Operate::ConfirmDelUser ) {
    if ( users.size() <= 1 ) {
      IO::PrintDelUserError();
      control = Control::User;
      return;
    }
    IO::PrintDelUser(user_name);
    users.erase(users.begin() + curr_user);
    if ( static_cast<std::size_t>(curr_user) >= users.size() - 1) {
      curr_user = users.size() - 1;
    }
    control = Control::User;
  } else if ( op == Operate::Unknown ) {
    IO::PrintInputError(str);
  } else if ( op == Operate::CanCelDelUser ) {
    IO::PrintCancelDelUser(user_name);
    control = Control::User;
  }
}

// 背包介面：使用道具、查看背包，或只查看技能庫。
void Editor::OperateBackpack(Operate op, std::string str) {
  User& user = users[curr_user];
  if ( op == Operate::Unknown ) {
    IO::PrintInputError(str);
  } else if ( op == Operate::QuitBackpack) {
    IO::PrintQuitBack();
    control = Control::DogDoing;
  } else if ( op == Operate::HelpBackpack) {
    IO::HelpBackpack();
  } else if ( op == Operate::ListBackpack ) {
    user.ListBackpack();
  } else if ( op == Operate::SkillLibrary ) {
    user.ListSkillLibrary();
  } else if ( op == Operate::UseItem ) {
    // 若道具目標是刀盾，先進入選擇刀盾介面。
    ItemType type = user.GetItemOfBackpack(use_item_of_bp);
    ItemInfo info = ItemDatabase::GetInfo(type);
    if ( type != ItemType::None &&
         info.target == ItemTargetType::DogDoing ) {
      control = Control::SelectTargetDD;
      IO::PrintSelectDD(user.GetAllDDtitleInfo(), info.name);
      return;
    }
    user.UseItem(use_item_of_bp);
    user.ListBackpack(false);
    use_item_of_bp = -1;
  }
}

// 道具需要指定刀盾時，這裡負責接收目標刀盾編號。
void Editor::OperateSelectTargetDD(Operate op, std::string str) {
  User& user = users[curr_user];
  if ( op == Operate::Unknown ) {
      IO::PrintInputError(str);
    } else if ( op == Operate::HelpSelectTargetDD ) {
      IO::HelpSelecttargetDD();
    } else if ( op == Operate::BacktoBackpack ) {
      select_dd_index = -1;
      IO::PrintBackToBackpack();
      user.ListBackpack(false);
      control = Control::Backpack;
    } else if ( op == Operate::SelectTargetDD ) {
      // 使用完成後清掉暫存編號，回到背包。
      user.UseItem(use_item_of_bp, select_dd_index);
      
      use_item_of_bp = -1;
      select_dd_index = -1;
      control = Control::Backpack;
      user.ListBackpack(false);
    }
  }

// 裝備技能介面：先由 eq1~eq4 決定格子，再用技能庫編號選技能。
void Editor::OperateEquipSkill(Operate op, std::string str) {
  User& user = users[curr_user];
  if ( op == Operate::Unknown ) {
    IO::PrintInputError(str);
  } else if ( op == Operate::BacktoDD ) {
    equip_skill_slot = -1;
    control = Control::DogDoing;
    IO::PrintBacktoDD();
  } else if ( op == Operate::SkillLibrary ) {
    IO::PrintEquipSkillPrompt(equip_skill_slot);
    user.ListSkillLibrary();
  } else if ( op == Operate::EquipSkill ) {
    // User 會負責檢查普攻格、技能是否已被其他刀盾裝備。
    user.EquipSkillToCurrentDD(equip_skill_slot, std::stoi(str));
    equip_skill_slot = -1;
    control = Control::DogDoing;
  }
}

// 探索選單：選擇要挑戰的怪物，start 後才進入 Battle。
void Editor::BattleTest() {
  int selected_enemy = 1;
  int enemy_count = 13;
  std::string op;

  IO::PrintBattleTestMenu(selected_enemy);
  while ( true ) {
    IO::PrintOperateWating();
    if ( IO::GetToken(op) == false ) {
      IO::PrintCinError();
      continue;
    }

    op = ToLower(op);
    if ( op == "start" ) {
      // 使用目前選中的怪物開始戰鬥。
      StartBattleTest(selected_enemy);
      return;
    }
    if ( op == "help" || op == "h" ) {
      IO::PrintBattleTestHelp();
    } else if ( op == "list" || op == "l" ) {
      IO::PrintBattleTestMenu(selected_enemy);
    } else if ( op == "back" || op == "b" ) {
      IO::PrintBacktoDD();
      return;
    } else if ( IsDigit(op) ) {
      // 數字只切換選中的怪物，不會立刻開戰。
      int select = std::stoi(op);
      if ( select < 1 || select > enemy_count ) {
        IO::PrintBattleTestError();
        continue;
      }
      selected_enemy = select;
      IO::PrintBattleTestSelect(selected_enemy);
    } else {
      IO::PrintInputError(op);
    }
  }
}

// 依照探索選單的編號建立怪物，戰鬥勝利後處理技能掉落。
void Editor::StartBattleTest(int enemy_index) {
  User& user = users[curr_user];
  std::unique_ptr<Enemy> enemy;
  if ( enemy_index == 1 ) {
    enemy = std::make_unique<FireSlime>();
  } else if ( enemy_index == 2 ) {
    enemy = std::make_unique<WaterSlime>();
  } else if ( enemy_index == 3 ) {
    enemy = std::make_unique<GrassSlime>();
  } else if ( enemy_index == 4 ) {
    enemy = std::make_unique<ThunderSlime>();
  } else if ( enemy_index == 5 ) {
    enemy = std::make_unique<DarkSlime>();
  } else if ( enemy_index == 6 ) {
    enemy = std::make_unique<LightSlime>();
  } else if ( enemy_index == 7 ) {
    enemy = std::make_unique<Goblin>();
  } else if ( enemy_index == 8 ) {
    enemy = std::make_unique<Vampire>();
  } else if ( enemy_index == 9 ) {
    enemy = std::make_unique<DemonHunter>();
  } else if ( enemy_index == 10 ) {
    enemy = std::make_unique<StoneGuardian>();
  } else if ( enemy_index == 11 ) {
    enemy = std::make_unique<OrcWarrior>();
  } else if ( enemy_index == 12 ) {
    enemy = std::make_unique<VampireDuke>();
  } else if ( enemy_index == 13 ) {
    enemy = std::make_unique<AbyssKing>();
  }

  if ( enemy == nullptr ) {
    IO::PrintBattleTestError();
    return;
  }

  Battle battle(user, user.GetCurrentDD(), *enemy);
  battle.Run();
  if ( user.GetCurrentDD().GetHp() > 0 ) {
    // 掉落只會從這隻怪物自己擁有的技能中抽。
    user.TryDropSkill(enemy->GetAllSkillID());
  }
}

// 設定商店販售的商品。
void Editor::SetUpShop() {
  shop.AddProduct(new ProductDD());
  shop.AddProduct(new ProductSkillJar());
  shop.AddProduct(new ProductSmallHealPotion());
  shop.AddProduct(new ProductSmallExpPotion());
}

std::vector<std::string> Editor::GetUserNameArray() const {
  std::vector<std::string> names;
  for ( const User& user : users ) {
    names.push_back(user.GetUserName());
  }
  return names;
}

// 整個遊戲主迴圈：讀取輸入後，依目前介面分派給對應處理函式。
void Editor::Run() {
  Start();
  NewUser();
  SetUpShop();
  IO::PrintHelpHint();
  std::string str;
  Operate op = Operate::None;
  while ( op != Operate::Quit ) {     
    IO::PrintOperateWating();
    if ( !IO::GetToken(str) ) {
      IO::PrintCinError();
      continue;
    }
    op = GetOp(str);
    if ( control == Control::DogDoing ) {
      OperateDogDoing(op, str);
    } else if ( control == Control::Shop ) {
      OperateShop(op, str);
    } else if ( control == Control::Buy ) {
      OperateBuy(op, str);
    } else if ( control == Control::User ) {
      OperateUser(op, str);
    } else if ( control == Control::DelUser ) {
      OperateDelUser(op, str);
    } else if ( control == Control::Backpack ) {
      OperateBackpack(op, str);
    } else if ( control == Control::SelectTargetDD ) {
      OperateSelectTargetDD(op, str);
    } else if ( control == Control::EquipSkill ) {
      OperateEquipSkill(op, str);
    }
  }
}
