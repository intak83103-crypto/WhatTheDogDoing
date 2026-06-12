#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include "DisplayData.h"

class Creature{
private:
  std::string name;
  double hp;
  double max_hp;
  double mp;
  double max_mp;
  double attack;
  int speed;

public:
  Creature();
  Creature(CreatureInfo info);
  std::string GetName() const;
  double GetATK() const;
  double GetHp() const;
  double GetMp() const;
  int GetSpeed() const;
  double GetMaxHp() const;
  double GetMaxMp() const;
  void SetHp(double hp);
  void SetMaxHp(double max_hp);
  void SetMp(double mp);
  void SetMaxMp(double max_mp);
  void SetATK(double atk);
  void SetSpeed(int speed);
  virtual void PrintInfo() const = 0;
  void SetName(std::string name);
  void Heal(int heal);
  CreatureInfo GetCreatureInfo() const;
  virtual ~Creature() = default;
};



#endif