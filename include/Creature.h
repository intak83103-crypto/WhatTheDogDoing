#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>
#include "DisplayData.h"



class Creature{
private:
  Element element = None;
  SkillID skill_list[4] = {SkillID::None ,SkillID::None, SkillID::None, SkillID::None};
  int skill_cd[4] = {0, 0 ,0 ,0};
  int num_of_skill = 0;
  std::string name;
  int hp = 0;
  int max_hp = 0;
  int attack = 0;
  int speed = 0;
  int hit_rate = 95;             // 命中率
  int crit_rate = 20;            // 爆擊率
  int dodge_rate = 5;           // 閃避率
  int damage_increase = 0;       // 增傷
  int ult_energy = 0;
  int max_ult_energy = 100;
  

public:
  Creature();
  Creature(CreatureInfo info);
  std::string GetName() const;
  int GetATK() const;
  int GetHp() const;
  int GetSpeed() const;
  int GetMaxHp() const;
  void SetHp(int hp);
  void SetMaxHp(int max_hp);
  void SetATK(int atk);
  void SetSpeed(int speed);
  virtual void PrintInfo() const = 0;
  void SetName(std::string name);
  void Heal(int heal);
  CreatureInfo GetCreatureInfo() const;
  virtual ~Creature() = default;
  int GetCritRate() const;
  int GetHitRate() const;
  int GetDodgeRate() const;
  int GetDamageIncrease() const;
  Element GetElement() const;
  int GetUltEnergy() const;
  int GetMaxUltEnergy() const;
  bool CanUseUlt() const;
  void SetElement(Element element);
  void SetMaxUltEnergy(int max_ult_energy);
  void AddUltEnergy(int value);
  void UseUltEnergy();
  bool AddSkill(SkillID skill);
  bool DeleteSKill(int index);
  SkillID GetIndexOfSkillList(int index) const;
  void MinusHp(int minus);
  int GetNumOfSkill() const;
  void SetNumOfSkill(int num);
  int GetSkillCD(int index) const;
  bool CanUseSkill(int index) const;
  void SetSkillCd(int index, int cd);
  void ReduceSkillCD();
  void ReSetSkillCD(int index);
  void ResetSkillCD();
  void ListSkill() const;
  virtual void PrintBattleInfo() const = 0 ;
};



#endif
