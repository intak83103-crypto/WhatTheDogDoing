#include "../include/DogDoing.h"
#include "../include/Random.h"
#include <cstddef>


const std::vector<DogDoing::LevelData> DogDoing::level_table = {
  // 等級， 經驗值， 血量， 攻擊， 速度
  {1, 0,   50,  10, 10},
  {2, 20,  58,  11, 10},
  {3, 60,  72,  13, 11},
  {4, 115, 83,  14, 12},
  {5, 190, 96,  16, 14},
  {6, 280, 104, 17, 15},
  {7, 380, 112, 18, 15},
  {8, 520, 130, 22, 17}


};


void DogDoing::Init() {
  rank = 1;
  level = 1;
  SetHp(50);
  SetMaxHp(50);
  SetATK(10);
  SetSpeed(10);
  exp = 0;
  RanDomElement();
  AddSkill(SkillID::NormalAttack);
  AddSkill(SkillID::Heal);
  AddSkill(SkillID::Vampire_Drain);
}

void DogDoing::ApplyLevelData() {
  const LevelData& data = level_table[level - 1];
  SetMaxHp(data.max_hp);
  SetATK(data.attack);
  SetSpeed(data.spped);
  SetHp(GetMaxHp());
}

DogDoing::DogDoing() {}

DogDoing::DogDoing(int i) {
  Init();
  SetName("DogDoing_" + std::to_string(i));
  IO::PrintDDSetUp({GetName(), rank, level, GetElement()});
}

DogDoing::DogDoing(std::string name) {
  Init();
  SetName(name);
  IO::PrintDDSetUp({GetName(), rank, level, GetElement()});
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
  int n = level_table.size();
  int new_level = level;
  IO::PrintGetExp(GetName(), value);

  for ( int i = 0; i < n; i++ ) {
    if ( exp >= level_table[i].need_exp ) {
      new_level = level_table[i].level;
    }
  }

  if ( new_level > level ) {
    level = new_level;
    IO::PrintDDLevelUp(GetName());
    ApplyLevelData();
  }
}


DDtitleInfo DogDoing::TitlePackage() const{
  return {GetName(), rank, level, GetElement()};
}

DDInfo DogDoing::InfoPackage() const {
  DDtitleInfo title = TitlePackage();
  CreatureInfo property = GetCreatureInfo();
  return {title, property};
}

int DogDoing::GetCrit() const {
  return crit;
}

void DogDoing::RanDomElement() {
  bool is_none = Random::RandomChance(30);
  if ( is_none ) {
    SetElement(Element::None);
    return;
  }
    
  int element = Random::RandomInt(1, 6);
    
  if ( element == 1 ) {
    SetElement(Element::Fire);
  } else if ( element == 2 ) {
    SetElement(Element::Water);
  } else if ( element == 3 ) {
    SetElement(Element::Grass);
  } else if ( element == 4 ) {
    SetElement(Element::Thunder);
  } else if ( element == 5 ) {
    SetElement(Element::Dark);
  } else if ( element == 6 ) {
    SetElement(Element::Light);
  } 
}

void DogDoing::PrintBattleInfo() const {
  IO::PrintDDInfo(InfoPackage());
  ListSkill();
}
