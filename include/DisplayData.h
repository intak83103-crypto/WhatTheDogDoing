#ifndef DISPLAY_DATA_H
#define DISPLAY_DATA_H
  
#include <string>
#include "skill.h"

struct DDtitleInfo{
  std::string name;
  int rank;
  int level;
};

enum Element{
  Fire, Water, Thunder, Grass, Dark, None
};

struct CreatureInfo{
  int hp;
  int max_hp;
  int attack;
  int speed;
  std::string name;
  Element element;
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
