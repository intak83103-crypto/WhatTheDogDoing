#ifndef DISPLAY_DATA_H
#define DISPLAY_DATA_H
  
#include <string>

enum Element{
  Fire, Water, Thunder, Grass, None
};

enum UltType{
  PowerUlt, HealUlt, NoUlt
};

struct DDtitleInfo{
  std::string name;
  int rank;
  int level;
};


struct CreatureInfo{
  int hp;
  int max_hp;
  int mp;
  int max_mp;
  int attack;
  int speed;
  std::string name;
  Element element;
  UltType ult_type;
  int ult_energy;
  int max_ult_energy;
};

struct DDInfo{
  DDtitleInfo title;
  CreatureInfo property;
};


struct ProductInfo{
  std::string name;
  int price;
};

struct UserInfo {
  std::string name;
  int num_of_dd;
  int coin;
};

struct BackpackInfo{
  std::string name;
  int count;
};




#endif
