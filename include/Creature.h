#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include "DisplayData.h"



class Creature{
private:
  Element element = None;
  UltType ult_type = NoUlt;
  std::string name;
  int hp = 0;
  int max_hp = 0;
  int mp = 0;
  int max_mp = 0;
  int attack = 0;
  int speed = 0;
  int hit_rate = 90;             // 命中率
  int crit_rate = 20;            // 爆擊率
  int dodge_rate = 10;           // 閃避率
  int damage_increase = 0;       // 增傷
  int ult_energy = 0;
  int max_ult_energy = 100;
  

public:
  Creature();
  Creature(CreatureInfo info);
  std::string GetName() const;
  int GetATK() const;
  int GetHp() const;
  int GetMp() const;
  int GetSpeed() const;
  int GetMaxHp() const;
  int GetMaxMp() const;
  void SetHp(int hp);
  void SetMaxHp(int max_hp);
  void SetMp(int mp);
  void SetMaxMp(int max_mp);
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
  UltType GetUltType() const;
  int GetUltEnergy() const;
  int GetMaxUltEnergy() const;
  bool CanUseUlt() const;
  void SetElement(Element element);
  void SetUltType(UltType ult_type);
  void SetMaxUltEnergy(int max_ult_energy);
  void AddUltEnergy(int value);
  void UseUltEnergy();
};



#endif
