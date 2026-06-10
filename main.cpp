#include <iostream>
#include <string>
#include <vector>
#include <random>   
#include <iomanip>  
#include <cctype>

class DogDoing;
class User;
class Product;


class IO{  //  Input / Output
public:
  static void PrintDot(int dot) {
    for ( int i = 0; i < dot; i++ ) {
      std::cout << "." << std::endl;;
    }
  }
  static bool GetToken(std::string& token) {
    if ( std::cin >> token ) {
      return true;
    }
    return false;
  }
  static void Divider() {
    std::cout << "-----------------------------------------------------------" << std::endl;
  }
  static void Divider(int n) {
    for ( int i = 0; i < n; i++ ) {
      Divider();
    }
  }
  static void PrintNewUser() {
    PrintDot(9);
    std::cout << "創建新的用戶中..." << std::endl;
    std::cout << "請輸入用戶名 :  " << std::endl;
  }
  static void PrintUserSetUp(const std::string& name, const int& id) {
    PrintDot(7);
    Divider();
    std::cout  << "Hi! " << name << " , User ID : " << id << std::endl;
    Divider();
  }
  static void PrintDDSetUp(const DogDoing& dd);
  static void FirstDD() {
    std::cout << "獲得第一隻刀盾!!" << std::endl;
  }
  static void PrintDDInfo(const DogDoing& dd);
  static void PrintRank(int rank) {
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
  static void EditorStart() {
    PrintDot(7);
    Divider();
    std::cout << "\n我的刀盾！ | What The Dog Doing?\n" << std::endl;
    Divider();
  }
  static void PrintOperateWating() {
    Divider();
    PrintDot(3);
    Divider();
    std::cout << "  (請輸入操作...) " << std::endl;
    Divider();
  }
  static void PrintHelpHint() {
    std::cout << std::endl;
    std::cout << "Hint : 隨時輸入 Help / h 列出指令列表" << std::endl;
  }
  static void PrintCinError() {
    std::cout << "讀取失敗" << std::endl;
  }
  static void PrintHelpDD(std::string name) {
    PrintDot(9);
    Divider();
    std::cout << "HELP!" << std::endl;
    Divider();
    std::cout << "L / List  | 列出" << name << "的所有刀盾 " << std::endl;
    std::cout << "D / DD    | 查看當前刀盾數值" << std::endl;
    std::cout << "R / Rn    | 更改目前刀盾名稱" << std::endl;
    std::cout << "S / Shop  | 查看商店" << std::endl;
    std::cout << "M / Me    | 查看" << name << "的資訊" << std::endl;
    std::cout << "U / User  | 進入使用者介面" << std::endl;

  }
  static void ListAllDD(User& user);
  static void PrintRenameInfo(std::string name) {
    PrintDot(9);
    std::cout << "更改 " << name << " 的名稱為：" << std::endl;
  }
  static void PrintRenameSuccess(const DogDoing& dd) {
    std::cout << "改名成功" << std::endl;
    PrintDDInfo(dd);
  }
  static void PrintDDtitle(const DogDoing& dd);
  static void PrintInputError(std::string str) {
    PrintDot(9);
    std::cout << "未知指令 : " << str << std::endl;
    PrintHelpHint();
  }
  static void PrintProduct(const Product& product);
  static void ListProduct(const std::vector<Product*>& products, int coin);
  static void PrintHelpShop() {
    PrintDot(9);
    Divider();
    std::cout << "HELP!" << std::endl;
    Divider();
    std::cout << "          | 輸入商品編號購買" << std::endl;
    std::cout << "Q / Quit  | 離開商店" << std::endl;
    std::cout << "L / list  | 列出商店物品" << std::endl; 
  }
  static void PrintQuitShop() {
    PrintDot(9);
    Divider();
    std::cout << "離開商店" << std::endl;
  }
  static void PrintNotEnoughCoin() {
    PrintDot(9);
    std::cout << "coin不足! " << std::endl;
  }
  static void PrintUserInfo(const User& user);
  static void PrintBuySuccess(const User& user, Product* product);
  static void PrintBuyHelp() {
    PrintDot(9);
    Divider();
    std::cout << "HELP!" << std::endl;
    Divider();
    std::cout << "Y / Yes   | 確認購買" << std::endl;
    std::cout << "N / no    | 取消購買" << std::endl;
  }
  static void PrintBuyInfo(Product* product);
  static void PrintBuyCancel() {
    PrintDot(9);
    Divider();
    std::cout << "取消購買" << std::endl;
  }
  static void PrintBuyError() {
    PrintDot(9);
    Divider();
    std::cout << "找不到這個商品" << std::endl;
  }
  static void PrintSwitchDDError() {
    PrintDot(9);
    Divider();
    std::cout << "找不到這個刀盾" << std::endl;
  }
  static void PrintSwitchDDSuccess(DogDoing& dd);
  static void PrintShop() {
    PrintDot(9);
    Divider();
    std::cout << "進入商店" << std::endl;
    Divider();
  }
  static void PrintUser() {
    PrintDot(9);
    Divider();
    std::cout << "進入使用者介面" << std::endl;
  }
  static void PrintHelpUser() {
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
  static void PrintSetUserName(std::string name);
  static void ListAllUser(std::vector<User> &users, int index);
  static void PrintBacktoDD() {
    PrintDot(9);
    Divider();
    std::cout << "已回到刀盾頁面" << std::endl;
  }
  static void PrintConfirmDelUser(std::string name);
  static void PrintDelUser(std::string name) {
    PrintDot(9);
    Divider();
    std::cout << "已刪除 : " << name  <<std::endl;
  }
  static void PrintCancelDelUser(std::string name) {
    PrintDot(9);
    Divider();
    std::cout << "取消刪除 : " << name << std::endl;
  }
  static void PrintDelUserError() {
    PrintDot(9);
    Divider();
    std::cout << "Error : 無法刪除最後一位使用者" << std::endl;
  }
  static void PrintDelUserHelp() {
    PrintDot(9);
    Divider();
    std::cout << "HELP!" << std::endl;
    Divider();
    std::cout << "Y / Yes   | 確認刪除" << std::endl;
    std::cout << "N / no    | 取消刪除" << std::endl;
  }
  static void PrintSwitchUserError() {
    PrintDot(9);
    Divider();
    std::cout << "用戶不存在" << std::endl;
  }
  static void PrintSwitchUser(std::string name) {
    PrintDot(9);
    Divider();
    std::cout << "已切換至 : " << name << std::endl;
  }
  static void PrintBuyDone(std::string name) {
    PrintDot(9);
    Divider();
    std::cout << "已購買 : " << name << std::endl;
  }
};





class Item {
private:
  std::string name;
public:
  virtual ~Item() {}
  virtual void Use(User& user) = 0;
  virtual std::string GetName() {
    return name;
  }
};




class Product{
private:
  int price;
  std::string name;
public:

  Product() {}
  Product(std::string name, int price) {
    this->price = price;
    this->name = name;
  }
  virtual ~Product() {}

  virtual void Apply(User& user) const = 0;

  std::string GetName() const {
    return name;
  }
  int GetPrice() const {
    return price;
  }
  void PrintProduct() {
    IO::PrintProduct(*this);
  }
};

void IO::PrintProduct(const Product& product) {
  std::cout << " $"  << std::setw(4)
            << product.GetPrice() << "  | " << product.GetName();
}





class Shop{
private:
  std::vector<Product*> products;
public:
  void ListProduct(int coin) {
    IO::ListProduct(products, coin);
  }
  void AddProduct(Product* p) {
    products.push_back(p);
  }

  ~Shop() {
    int n = products.size();
    for ( int i = 0; i < n; i++ ) {
      delete products[i];
    }
  }
  void Buy(int index, User& user);
  Product* GetProduct(int index) {
    return products[index - 1];
  }
  int GetNumOfProduct() {
    return products.size();
  }
};


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
};



class DogDoing {      //   刀盾
private:
  struct LevelData {
    int level;
    int need_exp;
    double max_hp;
    double max_mp;
    double attack;
  };

  static const std::vector<LevelData> level_table;

  static int nums_of_dd;
  float exp;            // 經驗值
  int rank;             // 星級
  double hp;            // 血量
  double max_hp;        // 血量上限
  double mp;            // 魔力
  double max_mp;        // 魔力上限
  double attack;        // 攻擊力
  int level;            // 等級
  std::string name;     // 名字
  
  void Init() {
    rank = 1;
    level = 1;
    hp = 50;
    max_hp = 50;
    mp = 3;
    max_mp = 3;
    attack = 10;
    exp = 0;
  }

  void ApplyLevelData() {
    const LevelData& data = level_table[level - 1];

    max_hp = data.max_hp;
    max_mp = data.max_mp;
    attack = data.attack;
    hp = max_hp;
    mp = max_mp;
  }

public:
  DogDoing() {}

  explicit DogDoing(int i) {
    Init();
    name = "DogDoing_" + std::to_string(i);
    nums_of_dd++;
    IO::PrintDDSetUp(*this);
  }

  explicit DogDoing(std::string name) {
    Init();
    nums_of_dd++;
    this->name = name;
    IO::PrintDDSetUp(*this);
  }

  std::string GetName() const{
    return name;
  }
  double GetHp() const{
    return hp;
  }
  double GetMp() const{
    return mp;
  }
  double GetATK() const{
    return attack;
  }
  int GetLevel() const{
    return level;
  }
  int GetRank() const{
    return rank;
  }
  double GetMaxHp() const{
    return max_hp;
  }
  double GetMaxMp() const{
    return max_mp;
  }
  void PrintInfo() const {
    IO::PrintDDInfo(*this);
  }
  void SetName(std::string name) {
    this->name = name;
    IO::PrintRenameSuccess(*this);
  }
  void AddExp(int value) {
    exp = exp + value;

    while ( level < level_table.size() &&
            exp >= level_table[level].need_exp ) {
      level = level + 1;
      ApplyLevelData();
    }
  }
};

const std::vector<DogDoing::LevelData> DogDoing::level_table = {
  {1, 0, 50, 3, 10},
  {2, 20, 60, 4, 13},
  {3, 50, 75, 5, 17},
  {4, 90, 95, 6, 22},
  {5, 140, 120, 8, 30}
};


int DogDoing::nums_of_dd = 1;

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

void IO::PrintDDtitle(const DogDoing& dd) {
  PrintRank(dd.GetRank());
  std::cout << " | LV." << std::setfill('0') << std::setw(2) 
            << dd.GetLevel() << " | " << dd.GetName();
  std::cout << std::setfill(' ');
}






class User {
private:
  std::string name;
  int id;
  int curr_dd = -1;
  std::vector<DogDoing> dogdoings;
  int coin;
  int id_of_dd;

public:

  User() {}
  explicit User(std::string name, int id) {
    this->name = name;
    this->id = id;
    id_of_dd = 1;
    IO::PrintUserSetUp(name,id);
    std::string dd_name;
    IO::FirstDD();
    dogdoings.emplace_back(DogDoing(id_of_dd++));
    curr_dd = 0;
    coin = 200;
  }
  int GetNumOfDD() const {
    return dogdoings.size();
  }
  DogDoing& GetCurrentDD() {
    return dogdoings[curr_dd];
  }
  int GetCurrDDIndex() const {
    return curr_dd;
  }
  std::string GetUserName() const{
    return name;
  }
  void SetName() {
    std::string str;
    IO::PrintSetUserName(name);
    IO::GetToken(str);
    name = str;
    PrintInfo();
  }
  DogDoing& GetDD(int index) {
    return dogdoings[index];
  }
  void AddDD() {
    dogdoings.emplace_back(DogDoing(id_of_dd++));
    curr_dd = dogdoings.size() - 1;
  }
  int GetCoin() const {
    return coin;
  }
  void AddCoin(int coins) {
    coin += coins;
  }
  bool PayCoin(int price) {
    if ( price > coin ) {
      IO::PrintNotEnoughCoin();
      return false;
    }
    coin -= price;
    return true;
  }
  void PrintInfo() const {
    IO::PrintUserInfo(*this);
  }

  void SwitchDD(int index) {
    if ( index <= 0 || index > dogdoings.size() ) {
      IO::PrintSwitchDDError();
      return;
    }
    curr_dd = index - 1;
    IO::PrintSwitchDDSuccess(dogdoings[curr_dd]);

  }
  

};

void IO::PrintDDSetUp(const DogDoing& dd) {
  std::cout << "獲得刀盾 : ";
  PrintDDtitle(dd);
  std::cout << std::endl;
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
 
void IO::PrintBuyInfo(Product* product) {
  PrintDot(9);
  Divider();
  std::cout << "確認花費 $" << product->GetPrice()
            << " 購買 " << product->GetName() << " ? ( Y / N )" << std::endl;
}

void IO::PrintSwitchDDSuccess(DogDoing& dd) {
  PrintDot(9);
  Divider();
  std::cout << "已切換至" << dd.GetName() << std::endl;
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

void IO::PrintConfirmDelUser(std::string name) {
  PrintDot(9);
  Divider();
  std::cout << "確認刪除 " << name << " ? ( Y / N ) "  << std::endl;
}

void Shop::Buy(int index, User& user) {
  if ( index <= 0 || index > products.size() ) {
    IO::PrintBuyError();
    return;
  }

  Product* product = products[index - 1];

  if ( user.PayCoin(product->GetPrice()) ) {
    IO::PrintBuyDone(product->GetName());
    product->Apply(user);
  }
}

class ProductDD : public Product {
public:
  ProductDD() : Product("新的刀盾", 100) {}

  void Apply(User& user) const override  {
    user.AddDD();
  }

};

class ProductHealPotion : public Product {
public:
  ProductHealPotion() : Product("治療藥水", 20) {}

  void Apply(User& user) const override {
    IO::PrintDot(9);

  }
};




enum class Control {  // 在Editor裡需要知道現在在操控的是什麼
  User, DogDoing, Shop, Buy, None, DelUser
};
enum class Operate{   // 可操控選項
  None, PrintInfo, ListDD, Quit, HelpDD, HelpUser, RenameDD, Unknown, SwitchDD,
  Shop, HelpShop, QuitShop, ListShop, GetUserInfo, Buy,
  HelpBuy, ConfirmBuy, CancelBuy, 
  User, AddUser, DelUser, ReNameUser, QuitUser, ListUser, BacktoDD, SwitchUser,
  ConfirmDelUser, CanCelDelUser, ConfirmDel, CanCelDel, HelpDelUser
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

  void NewUser() {
    std::string user_name;
    IO::PrintNewUser();
    IO::GetToken(user_name);
    num_of_user += 1;
    User user(user_name, num_of_user);
    users.push_back(user);
    curr_user = users.size() - 1;
  }
  void Start() {
    IO::EditorStart();
  }
  std::string ToLower(std::string str ) {
    for ( char& c : str ) {
      c = tolower(c);
    }
    return str;
  }

  bool IsDigit(std::string str) {
    for (char& c : str ) {
      if ( !isdigit(c) )
        return false;
    }
    return true;
  }
  
  Operate GetOp(std::string op) {
    op = ToLower(op);
    if ( control == Control::DogDoing ) {
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

    } else if ( control == Control::User ) {
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
      if ( op == "help" || op == "h" ) {
        return Operate::HelpShop;
      } 
      if ( IsDigit(op) ) {
        buy_index = std::stoi(op);
        return Operate::Buy;
      }
      if ( op == "q" || op == "quit" || op == "b" || op == "back" ) {
        return Operate::QuitShop;
      } 
      if ( op == "l" || op == "list" ) {
        return Operate::ListShop;
      } 


    } else if ( control == Control::Buy ) {
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
      if ( op == "h" || op == "help" ) {
        return Operate::HelpDelUser;
      } 
      if ( op == "y" || op == "yes" ) {
        return Operate::ConfirmDelUser;
      }
      if ( op == "n" || op == "no" ) {
        return Operate::CanCelDelUser;
      }
    }
    return Operate::Unknown;
  }

  void OperateDogDoing(Operate op, std::string str) {
    User& user = users[curr_user];
    int coin = user.GetCoin();
    if ( op == Operate::HelpDD ) {
      IO::PrintHelpDD(user.GetUserName());
    } else if ( op == Operate::Unknown ) {
      IO::PrintInputError(str);
    } else if ( op == Operate::PrintInfo ) {
      user.GetCurrentDD().PrintInfo();
    } else if ( op == Operate::ListDD ) {
      IO::ListAllDD(user);
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
    }
    
    else {
      IO::PrintCinError();
    }

  }
  
  void SetUpShop() {
    shop.AddProduct(new ProductDD());
  }

  void OperateShop(Operate op, std::string str) {
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
        IO::PrintBuyInfo(shop.GetProduct(product));
        control = Control::Buy;
      }
    }
    
  
  }
  bool ConfirmIndex(int index) {
    if ( index <= 0 || index > shop.GetNumOfProduct() ) {
      return false;
    }
    return true;
  }
  void OperateBuy(Operate op, std::string str ) {
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

  void OperateUser(Operate op, std::string str) {
    User& user = users[curr_user];
    if ( op == Operate::HelpUser ) {
      IO::PrintHelpUser();
    } else if ( op == Operate::ReNameUser ) {
      user.SetName();
    } else if ( op == Operate::Unknown ) {
      IO::PrintInputError(str);
    } else if ( op == Operate::ListUser ) {
      IO::ListAllUser(users, curr_user);
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
      if ( switch_user_index - 1 < 0 || switch_user_index - 1 >= users.size() ) {
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

  void OperateDelUser(Operate op, std::string str) {
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
      if ( curr_user >= users.size() - 1) {
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

public:
  void Run() {
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
      }



    }

  }
  
};



int main() {
  Editor editor;
  editor.Run();
}
