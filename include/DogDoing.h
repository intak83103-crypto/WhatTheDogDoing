#ifndef DOGDOING_H
#define DOGDOING_H

#include <string>
#include <vector>
#include "IO.h"
#include "DisplayData.h"
#include "Creature.h"

class DogDoing : public Creature{
private:
  struct LevelData {
    int level;
    int need_exp;
    double max_hp;
    double max_mp;
    double attack;
  };
  static const std::vector<LevelData> level_table;

  float exp;
  int rank;
  int level;

  void Init();
  void ApplyLevelData();

public:
  DogDoing();
  explicit DogDoing(int i);
  explicit DogDoing(std::string name);

  int GetLevel() const;
  int GetRank() const;
  void PrintInfo() const override;
  void PrintHealInfo() const override;
  void AddExp(int value);
  DDtitleInfo TitlePackage() const;
  DDInfo InfoPackage() const;
  
};

#endif
