#ifndef DISPLAY_DATA_H
#define DISPLAY_DATA_H
  
#include <string>

struct DDtitleInfo{
  std::string name;
  int rank;
  int level;
};


struct CreatureInfo{
  double hp;
  double max_hp;
  double mp;
  double max_mp;
  double attack;
  int speed;
  std::string name;
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