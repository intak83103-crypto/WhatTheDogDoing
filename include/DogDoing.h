#ifndef DOGDOING_H
#define DOGDOING_H

#include <string>
#include <vector>
#include "IO.h"
#include "DisplayData.h"


class DogDoing {
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

  float exp;
  int rank;
  double hp;
  double max_hp;
  double mp;
  double max_mp;
  double attack;
  int level;
  std::string name;

  void Init();
  void ApplyLevelData();

public:
  DogDoing();
  explicit DogDoing(int i);
  explicit DogDoing(std::string name);

  std::string GetName() const;
  double GetHp() const;
  double GetMp() const;
  double GetATK() const;
  int GetLevel() const;
  int GetRank() const;
  double GetMaxHp() const;
  double GetMaxMp() const;
  void PrintInfo() const;
  void SetName(std::string name);
  void AddExp(int value);
  void Heal(int heal);
  DDtitleInfo TitlePackage() const;
  DDinfo InfoPackage() const;
  
};

#endif
