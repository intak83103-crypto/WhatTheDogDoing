#include "../include/DogDoing.h"

#include <cstddef>

const std::vector<DogDoing::LevelData> DogDoing::level_table = {
  {1, 0, 50, 3, 10},
  {2, 20, 60, 4, 13},
  {3, 50, 75, 5, 17},
  {4, 90, 95, 6, 22},
  {5, 140, 120, 8, 30}
};

int DogDoing::nums_of_dd = 1;

void DogDoing::Init() {
  rank = 1;
  level = 1;
  hp = 50;
  max_hp = 50;
  mp = 3;
  max_mp = 3;
  attack = 10;
  exp = 0;
}

void DogDoing::ApplyLevelData() {
  const LevelData& data = level_table[level - 1];

  max_hp = data.max_hp;
  max_mp = data.max_mp;
  attack = data.attack;
  hp = max_hp;
  mp = max_mp;
}

DogDoing::DogDoing() {}

DogDoing::DogDoing(int i) {
  Init();
  name = "DogDoing_" + std::to_string(i);
  nums_of_dd++;
  IO::PrintDDSetUp({name, rank, level});
}

DogDoing::DogDoing(std::string name) {
  Init();
  nums_of_dd++;
  this->name = name;
  IO::PrintDDSetUp({name, rank, level});
}

std::string DogDoing::GetName() const {
  return name;
}

double DogDoing::GetHp() const {
  return hp;
}

double DogDoing::GetMp() const {
  return mp;
}

double DogDoing::GetATK() const {
  return attack;
}

int DogDoing::GetLevel() const {
  return level;
}

int DogDoing::GetRank() const {
  return rank;
}

double DogDoing::GetMaxHp() const {
  return max_hp;
}

double DogDoing::GetMaxMp() const {
  return max_mp;
}

void DogDoing::PrintInfo() const {
  DDinfo dd = InfoPackage();
  IO::PrintDDInfo(dd);
}

void DogDoing::SetName(std::string name) {
  this->name = name;
  DDinfo dd = InfoPackage();
  IO::PrintRenameSuccess(dd);
}

void DogDoing::AddExp(int value) {
  exp = exp + value;

  while ( static_cast<std::size_t>(level) < level_table.size() &&
          exp >= level_table[level].need_exp ) {
    level = level + 1;
    ApplyLevelData();
  }
}

void DogDoing::Heal(int heal) {
  hp += heal;
  if ( hp >= max_hp ) {
    hp = max_hp;
  }
}

DDtitleInfo DogDoing::TitlePackage() const{
  return {name, rank, level};
}

DDinfo DogDoing::InfoPackage() const {
  return {TitlePackage(), hp, max_hp, 
          mp, max_mp, attack};
}