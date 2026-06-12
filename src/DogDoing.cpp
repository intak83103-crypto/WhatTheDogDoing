#include "../include/DogDoing.h"

#include <cstddef>

const std::vector<DogDoing::LevelData> DogDoing::level_table = {
  {1, 0, 50, 3, 10},
  {2, 20, 60, 4, 13},
  {3, 50, 75, 5, 17},
  {4, 90, 95, 6, 22},
  {5, 140, 120, 8, 30}
};


void DogDoing::Init() {
  rank = 1;
  level = 1;
  SetHp(50);
  SetMaxHp(50);
  SetMp(3);
  SetMaxMp(3);
  SetATK(10);
  SetSpeed(10);
  exp = 0;
}

void DogDoing::ApplyLevelData() {
  const LevelData& data = level_table[level - 1];
}

DogDoing::DogDoing() {}

DogDoing::DogDoing(int i) {
  Init();
  SetName("DogDoing_" + std::to_string(i));
  IO::PrintDDSetUp({GetName(), rank, level});
}

DogDoing::DogDoing(std::string name) {
  Init();
  SetName(name);
  IO::PrintDDSetUp({name, rank, level});
}

int DogDoing::GetLevel() const {
  return level;
}

int DogDoing::GetRank() const {
  return rank;
}


void DogDoing::PrintInfo() const {
  DDInfo dd = InfoPackage();
  IO::PrintDDInfo(dd);
}


void DogDoing::AddExp(int value) {
  exp = exp + value;

  while ( static_cast<std::size_t>(level) < level_table.size() &&
          exp >= level_table[level].need_exp ) {
    level = level + 1;
    ApplyLevelData();
  }
}


DDtitleInfo DogDoing::TitlePackage() const{
  return {GetName(), rank, level};
}

DDInfo DogDoing::InfoPackage() const {
  DDtitleInfo title = TitlePackage();
  CreatureInfo property = GetCreatureInfo();
  return {title, property};
}

void DogDoing::PrintHealInfo() const {
  IO::HealSuccess(GetName(), GetHp());
}