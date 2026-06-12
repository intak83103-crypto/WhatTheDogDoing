#include "../include/Editor.h"

#include <cctype>
#include <cstddef>

#include "../include/IO.h"
#include "../include/Products.h"
#include "../include/Item.h"

void Editor::NewUser() {
  std::string user_name;
  IO::PrintNewUser();
  IO::GetToken(user_name);
  num_of_user += 1;
  User user(user_name, num_of_user);
  users.push_back(user);
  curr_user = users.size() - 1;
}

void Editor::Start() {
  IO::EditorStart();
}

std::string Editor::ToLower(std::string str ) {
  for ( char& c : str ) {
    c = tolower(c);
  }
  return str;
}

bool Editor::IsDigit(std::string str) {
  for (char& c : str ) {
    if ( !isdigit(c) )
      return false;
  }
  return true;
}

Operate Editor::GetOp(std::string op) {     // 在不同介面得到指令
  op = ToLower(op);
  if ( control == Control::DogDoing ) {     // 介面：刀盾
    if ( op == "help" || op == "h" ) {
      return Operate::HelpDD;
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

  } else if ( control == Control::User ) {    // 介面：使用者
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
    

  } else if ( control == Control::Shop ) {    // 介面：商店
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


  } else if ( control == Control::Buy ) {    // 介面：購買
    if ( op == "y" || op == "yes" ) {
      return Operate::ConfirmBuy;
    }
    if ( op == "h" || op == "help" ) {
      return Operate::HelpBuy;
    }
    if ( op == "n" || op == "no" ) {
      return Operate::CancelBuy;

    }
  } else if ( control == Control::DelUser ) {   // 介面：刪除使用者
    if ( op == "h" || op == "help" ) {
      return Operate::HelpDelUser;
    } 
    if ( op == "y" || op == "yes" ) {
      return Operate::ConfirmDelUser;
    }
    if ( op == "n" || op == "no" ) {
      return Operate::CanCelDelUser;
    }
  } else if ( control == Control::Backpack ) {  // 介面：背包
    if ( op == "h" || op == "help" ) {
      return Operate::HelpBackpack;
    }
    if ( op == "b" || op == "back" ) {
      return Operate::QuitBackpack;
    }
    if ( op == "l" || op == "list" ) {
      return Operate::ListBackpack;
    }
    if ( IsDigit(op) ) {
      use_item_of_bp = std::stoi(op);
      return Operate::UseItem;
    }
  } else if ( control == Control::SelectTargetDD ) {     // 介面：使用需要選擇刀盾的物品
    if ( op == "h" || op == "help" ) {
      return Operate::HelpSelectTargetDD;
    } else if ( IsDigit(op) ) {
      select_dd_index = std::stoi(op);
      return Operate::SelectTargetDD;
    } else if ( op == "b" || op == "back" ) {
      return Operate::BacktoBackpack;
    }
  }
  return Operate::Unknown;
}

void Editor::OperateDogDoing(Operate op, std::string str) {
  User& user = users[curr_user];
  int coin = user.GetCoin();
  if ( op == Operate::HelpDD ) {
    IO::PrintHelpDD(user.GetUserName());
  } else if ( op == Operate::Unknown ) {
    IO::PrintInputError(str);
  } else if ( op == Operate::PrintInfo ) {
    user.GetCurrentDD().PrintInfo();
  } else if ( op == Operate::ListDD ) {
    user.ListAllDD();
  } else if ( op == Operate::RenameDD ) {
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
    control = Control::Shop;
    IO::PrintShop();
    shop.ListProduct(user.GetCoin());
  } else if ( op == Operate::User ) {
    control = Control::User;
    IO::PrintUser();
    std::vector<std::string> users_name;
    for ( int i = 0; i < num_of_user; i++ ) {
      users_name.push_back(users[i].GetUserName());
    }
    IO::ListAllUser(users_name, curr_user);
  } else if ( op == Operate::Backpack ) {
    control = Control::Backpack;
    IO::PrintSwitchBackpack();
    std::vector<std::string> backpack;
    user.ListBackpack();
  }
  
  else {
    IO::PrintCinError();
  }
}

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
    int product = std::stoi(str);
    if ( ConfirmIndex(product) == false ) {
      IO::PrintBuyError();
    } else {
      IO::PrintBuyInfo(shop.GetProduct(product)->InfoPackage());
      control = Control::Buy;
    }
  }
}

bool Editor::ConfirmIndex(int index) {
  if ( index <= 0 || index > shop.GetNumOfProduct() ) {
    return false;
  }
  return true;
}

void Editor::OperateBuy(Operate op, std::string str ) {
  User& user = users[curr_user];
  if ( op == Operate::HelpBuy) {
    IO::PrintBuyHelp();
  } else if ( op == Operate::ConfirmBuy ) {
    shop.Buy(buy_index, user);
    control = Control::Shop;
    buy_index = -1;
  } else if ( op == Operate::CancelBuy ) {
    IO::PrintBuyCancel();
    control = Control::Shop;
    buy_index = -1;
  } else if ( op == Operate::Unknown ) {
    IO::PrintInputError(str);
  }
}

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
  } else if ( op == Operate::UseItem ) {
    Item* item = user.GetItemOfBackpack(use_item_of_bp);
    if ( item != nullptr ) {
      if ( item->GetItemTargetType() == ItemTargetType::DogDoing ) {
        control = Control::SelectTargetDD;
        IO::PrintSelectDD(user.GetAllDDtitleInfo(), item->GetName());
        return;
      }
    }
    user.UseItem(use_item_of_bp);
    use_item_of_bp = -1;
  }
}

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
      user.UseItem(use_item_of_bp, select_dd_index);
      
      use_item_of_bp = -1;
      select_dd_index = -1;
      control = Control::Backpack;
    }
  }

void Editor::SetUpShop() {
  shop.AddProduct(new ProductDD());
  shop.AddProduct(new ProductHealPotion());
}

std::vector<std::string> Editor::GetUserNameArray() const {
  std::vector<std::string> names;
  for ( User user : users ) {
    names.push_back(user.GetUserName());
  }
  return names;
}

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
    }
  }
}
