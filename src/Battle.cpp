#include <iostream>
#include "../include/Battle.h"

#include "../include/DogDoing.h"
#include "../include/Creature.h"
#include "../include/User.h"
#include "../include/Random.h"
#include "../include/IO.h"

Battle::Battle(User& user, DogDoing& dogdoing, Creature& enemy)
    : user(user), dogdoing(dogdoing), enemy(enemy) {
}

bool Battle::IsCrit(bool is_enemy) {
  int crit_rate = is_enemy ? enemy.GetCritRate() : dogdoing.GetCritRate();
  return Random::RandomChance(crit_rate);
}

bool Battle::IsHit(bool is_enemy) {
  SetOverHit(is_enemy, 0);
  int attacker_hit, defender_dodge;  // 攻擊方, 被攻擊方
  int attacker_speed, defender_speed;  
  if ( is_enemy ) {
    attacker_hit = enemy.GetHitRate();
    attacker_speed = enemy.GetSpeed();
    defender_dodge = dogdoing.GetDodgeRate();
    defender_speed = dogdoing.GetSpeed();
  } else {
    attacker_hit = dogdoing.GetHitRate();
    attacker_speed = dogdoing.GetSpeed();
    defender_dodge = enemy.GetDodgeRate();
    defender_speed = enemy.GetSpeed();
  }

  int hit_rate = attacker_hit + attacker_speed - defender_speed - defender_dodge;

  if ( hit_rate >= 100 ) {
    SetOverHit(is_enemy, hit_rate - 100);
    return true;
  } else {
    SetOverHit(is_enemy, 0);
    return Random::RandomChance(hit_rate);
  }
}

void Battle::SetOverHit(bool is_enemy, int over_hit) {
  if ( is_enemy == false ) {
    dd_over_hit = over_hit;
  } else {
    enemy_over_hit = over_hit;
  }
}

int Battle::CalculateDamage(int damage, bool is_enemy) {
  int final_damage = 0;
  if ( is_enemy ) {
    final_damage = damage;
    final_damage = (final_damage + enemy_over_hit)
        * (100 + enemy.GetDamageIncrease()) / 100;
    SetOverHit(is_enemy, 0);
    return final_damage;
  }

  final_damage = damage;
  final_damage = (final_damage + dd_over_hit)
      * (100 + dogdoing.GetDamageIncrease()) / 100;
  SetOverHit(is_enemy, 0);
  return final_damage;
}

void Battle::Run() {
  bool dd_first = dogdoing.GetSpeed() >= enemy.GetSpeed();

  while ( IsBattleOver() == false ) {
    if ( dd_first ) {
      DDTurn();
      if ( IsBattleOver() == false ) {
        EnemyTurn();
      }
    } else {
      EnemyTurn();
      if ( IsBattleOver() == false ) {
        DDTurn();
      }
    }
    turn++;
  }
}

void Battle::DDTurn() {
  std::string op;
  while ( true ) {
    IO::GetToken(op);
    if ( IsDigit(op) ) {
      int select_id = std::stoi(op);
      SkillID skill_id = dogdoing.GetIndexOfSkillList(select_id);

      if ( skill_id == SkillID::None ) {
        continue;
      } else {
        SkillInfo skill_info = SkillDataBase::GetSkillInfo(skill_id, dogdoing.GetATK());
        SkillDetail detail = SkillDataBase::GetSkillDetail(skill_info);
        SkillEffectApply(false, detail);
        return;
      }
    } else {
      // 輸入錯誤
    }
    
  }
}

void Battle::EnemyTurn() {
  int use_skill = Random::RandomInt(1, 1);
  SkillID skill_id = SkillID::None;
  if ( use_skill == 1 ) {
    skill_id = enemy.GetIndexOfSkillList(1);
  }
  SkillInfo skill_info = SkillDataBase::GetSkillInfo(skill_id, enemy.GetATK());
  SkillDetail detail = SkillDataBase::GetSkillDetail(skill_info);
  SkillEffectApply(true, detail);
}

bool Battle::IsBattleOver() const {
  return dogdoing.GetHp() <= 0 || enemy.GetHp() <= 0;
}


void Battle::SkillEffectApply(bool is_enemy, SkillDetail skill_detail) {
  int value = skill_detail.value;
  SkillEffect effect = skill_detail.effect;
  if ( effect == SkillEffect::Attack ) {
    if ( IsHit(is_enemy) ) {
      value = CalculateDamage(value, is_enemy);
      if ( IsCrit(is_enemy) ) {
        value = value * 150 / 100;
      }
      if ( is_enemy ) {
        dogdoing.MinusHp(value);
      } else {
        enemy.MinusHp(value);
      }
    } else {
      // 未命中
    }
  } else if ( effect == SkillEffect::Heal ) {
    if ( is_enemy ) {
      enemy.Heal(value);
    } else {
      dogdoing.Heal(value);
    }
  } else if ( effect == SkillEffect::Defend ) {

  } else if ( effect == SkillEffect::Buff ) {

  }
}

bool Battle::IsDigit(std::string str)  {
  for ( char c : str ) {
    if ( !isdigit(c) ) {
      return false;
    }
  }
  return true;
}

void Battle::SetTempAtk(bool is_enemy) {
  if ( is_enemy ) {
    
  } else {

  }
}