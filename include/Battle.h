#ifndef BATTLE_H
#define BATTLE_H

class User;
class DogDoing;
class Creature;

#include "DisplayData.h"
#include "skill.h"
#include "Enemy.h"

enum class BattleControl{
  Battle, Unknown, Quit
};
  
enum class BattleOperate;

struct BattleTempValue{
  int action_value = 0;
  int base_attack = 0;
  int base_hp = 0;
  int base_max_hp = 0;
  int base_speed = 0;
  int base_damage_increase = 0;
  int base_defend = 0;         //減傷
  int over_hit = 0;
  int base_crit_rate = 0;
  int base_hit_rate = 0;
  int base_dodge_rate = 0;
  int temp_attack = 0;
  int temp_hp = 0;
  int temp_max_hp = 0;
  int temp_speed = 0;
  int temp_damage_increase = 0;
  int temp_defend = 0;
  int temp_crit_rate = 0;
  int temp_hit_rate = 0;
  int temp_dodge_rate = 0;

};

class Battle{
private:
  User& user;
  DogDoing& dogdoing;
  Enemy& enemy;
  BattleControl control = BattleControl::Battle;
  BattleTempValue dd_value, enemy_value;
  bool game_run = true;
  int is_advantage = 0;  //屬性是否克制： 0：無  1 : 克制  2 : 被克制
  int select_skill = -1;
  std::vector<BuffInfo> dd_buff;
  std::vector<BuffInfo> enemy_buff;

  
public:
  Battle(User& user, DogDoing& dogdoing, Enemy& enemy); 
  int CalculateDamage(int damage, bool is_enemy = false);
  int BattleHeal(bool is_enemy, int heal);
  void ClampBattleHp(bool is_enemy);
  bool IsHit(bool is_enemy = false);
  bool IsCrit(bool is_enemy = false);
  void Run();
  void SetOverHit(bool is_enemy, int over_hit);
  bool IsBattleOver() const;
  void DDTurn(bool bonus_turn = false);
  void EnemyTurn(bool bonus_turn = false);
  bool IsDigit(std::string str);
  bool SkillEffectApply(bool is_enemy, SkillInfo SkillInfo);
  int CalculateSkillValue(bool is_enemy, SkillDetail skill_detail);
  void SetElementBonus();
  bool EnemyShouldUseSkill(int index);
  void Win();
  std::string ToLower(std::string str);
  BattleOperate GetOp(std::string);
  void SetBattleTempValue(bool is_enemy);
  bool HasBuff(bool is_enemy, BattleBuffType buff_type);
  int CalculateBuffValue(bool is_enemy, BuffInfo buff_info);
  void ApplyBuff(bool is_enemy, std::vector<BuffInfo> buff);
  void ApplyEraseBuff(bool is_enemy, BuffInfo erase_buff);
  void ReduceBuffRound(bool is_enemy);
  CreatureInfo GetBattleCreatureInfo(bool is_enemy);
};




#endif 
