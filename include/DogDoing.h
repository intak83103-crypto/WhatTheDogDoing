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
    int max_hp;
    int attack;
  };
  static const std::vector<LevelData> level_table;

  int exp;
  int rank;
  int level;
  int crit = 20;    // 爆擊機率：crit / 100， 傷害 x1.5

  void Init();
  void ApplyLevelData();

public:
  DogDoing();
  explicit DogDoing(int i);
  explicit DogDoing(std::string name);
  int GetCrit() const;
  int GetLevel() const;
  int GetRank() const;
  void PrintInfo() const override;
  void AddExp(int value);
  DDtitleInfo TitlePackage() const;
  DDInfo InfoPackage() const;
  
};

#endif
