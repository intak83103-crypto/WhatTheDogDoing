#ifndef BATTLE_H
#define BATTLE_H

class User;
class DogDoing;
class Creature;

#include "DisplayData.h"
#include "skill.h"
#include "Enemy.h"

class Battle{
private:
  User& user;
  DogDoing& dogdoing;
  Enemy& enemy;
  int turn = 1;
  int dd_over_hit = 0;
  int enemy_over_hit = 0;
  int temp_atk_of_dd = 0;
  int temp_atk_of_enemy = 0;
  int damage_increase_of_dd = 0;
  int damage_increase_of_enemy = 0;
  int defend_of_dd = 0;
  int defend_of_enemy;
  int is_advantage = 0;  //屬性是否克制： 0：無  1 : 克制  2 : 被克制
  
public:
  Battle(User& user, DogDoing& dogdoing, Enemy& enemy); 
  int CalculateDamage(int damage, bool is_enemy = false);
  bool IsHit(bool is_enemy = false);
  bool IsCrit(bool is_enemy = false);
  void Run();
  void SetOverHit(bool is_enemy, int over_hit);
  void Round();
  void Move();
  bool IsBattleOver() const;
  void DDTurn();
  void EnemyTurn();
  bool IsDigit(std::string str);
  void SkillEffectApply(bool is_enemy, SkillDetail skill_detail);
  void SetTempAtk(bool is_enemy);
  void SetElementBonus();
  bool EnemyShouldUseSkill(int index);
};




#endif 
