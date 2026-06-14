#include <iostream>
#include "../include/Battle.h"

#include "../include/DogDoing.h"
#include "../include/Creature.h"
#include "../include/User.h"
#include "../include/Random.h"
#include "../include/IO.h"

Battle::Battle(User& user, DogDoing& dogdoing, Enemy& enemy)
    : user(user), dogdoing(dogdoing), enemy(enemy) {
  SetElementBonus();
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
        * (100 + enemy.GetDamageIncrease() + damage_increase_of_enemy) / 100;
    SetOverHit(is_enemy, 0);
    return final_damage;
  }

  final_damage = damage;
  final_damage = (final_damage + dd_over_hit)
      * (100 + dogdoing.GetDamageIncrease() + damage_increase_of_dd) / 100;
  SetOverHit(is_enemy, 0);
  return final_damage;
}

void Battle::Run() {
  IO::PrintBattleStart(dogdoing.GetName(), enemy.GetName(), is_advantage);
  bool dd_first = dogdoing.GetSpeed() >= enemy.GetSpeed();


  while ( IsBattleOver() == false ) {
    IO::Pause(1);
    IO::PrintBattleTurnStart(turn);
    IO::PrintDot(1);
    IO::PrintBattleHpInfo(dogdoing.GetCreatureInfo());
    IO::PrintBattleHpInfo(enemy.GetCreatureInfo());
    IO::PrintDot(1);

    if ( dd_first ) {
      DDTurn();
      if ( IsBattleOver() == false ) {
        IO::Pause(1);
        EnemyTurn();
      }
    } else {
      EnemyTurn();
      if ( IsBattleOver() == false ) {
        IO::Pause(1);
        DDTurn();
      }
    }
    dogdoing.ReduceSkillCD();
    enemy.ReduceSkillCD();
    turn++;
  }
  IO::Pause(1);
  IO::PrintBattleEnd();
  dogdoing.ResetSkillCD();
  enemy.ResetSkillCD();
  if ( dogdoing.GetHp() <= 0 ) {
    IO::PrintBattleLose();
  } else {
    IO::PrintBattleWin();
  }
}

void Battle::DDTurn() {
  std::string op;
  IO::PrintBattleRoundStart(dogdoing.GetName());
  while ( true ) {
    IO::GetToken(op);
    if ( IsDigit(op) ) {
      int select_id = std::stoi(op);
      SkillID skill_id = dogdoing.GetIndexOfSkillList(select_id);

      if ( skill_id == SkillID::None ) {
        IO::PrintSkillSelectError();
        continue;
      } else {
        if ( dogdoing.CanUseSkill(select_id) ) {
          dogdoing.ReSetSkillCD(select_id);
          SkillInfo skill_info = SkillDataBase::GetSkillInfo(skill_id, dogdoing.GetATK());
          SkillEffectApply(false, skill_info);
          return;
        } else {
          IO::PrintSkillUnready();
        }
      }
    } else {
      IO::PrintInputError(op);
    }
    
  }
}

void Battle::EnemyTurn() {
  IO::PrintBattleRoundStart(enemy.GetName());
  int use_skill = 1;
  SkillID skill_id = SkillID::None;

  if ( enemy.GetNumOfSkill() > 1 ) {
    use_skill = Random::RandomInt(2, enemy.GetNumOfSkill());
    int try_count = 0;
    while ( EnemyShouldUseSkill(use_skill) == false && try_count < 10 ) {
      use_skill = Random::RandomInt(2, enemy.GetNumOfSkill());
      try_count++;
    }
    if ( EnemyShouldUseSkill(use_skill) == false ) {
      use_skill = 1;
    }
  }

  if ( use_skill == 1 ) {
    skill_id = enemy.GetIndexOfSkillList(1);
  } else if ( use_skill == 2 ) {
    skill_id = enemy.GetIndexOfSkillList(2);
  } else if ( use_skill == 3 ) {
    skill_id = enemy.GetIndexOfSkillList(3);
  } else if ( use_skill == 4 ) {
    skill_id = enemy.GetIndexOfSkillList(4);
  }
  SkillInfo skill_info = SkillDataBase::GetSkillInfo(skill_id, enemy.GetATK());
  enemy.ReSetSkillCD(use_skill);
  SkillEffectApply(true, skill_info);
}

bool Battle::EnemyShouldUseSkill(int index) {
  if ( enemy.CanUseSkill(index) == false ) {
    return false;
  }

  SkillID skill_id = enemy.GetIndexOfSkillList(index);
  SkillInfo skill_info = SkillDataBase::GetSkillInfo(skill_id, enemy.GetATK());

  if ( skill_info.main_use == SkillEffect::Heal &&
       enemy.GetHp() * 100 / enemy.GetMaxHp() > 80 ) {
    return false;
  }

  return true;
}

bool Battle::IsBattleOver() const {
  return dogdoing.GetHp() <= 0 || enemy.GetHp() <= 0;
}


void Battle::SkillEffectApply(bool is_enemy, SkillInfo skill_info) {
  int n = skill_info.skill_detail.size();
  IO::Pause(1);
  if ( is_enemy ) {
    IO::PrintUseSkill(enemy.GetName(), skill_info.skill_name);
  } else {
    IO::PrintUseSkill(dogdoing.GetName(), skill_info.skill_name);
  }

  for ( int i = 0; i < n; i++ ) {
    SkillDetail skill_detail = skill_info.skill_detail[i];
    int value = skill_detail.value;
    SkillEffect effect = skill_detail.effect;

    IO::Pause(1);
    if ( effect == SkillEffect::Attack ) {
      if ( IsHit(is_enemy) ) {
        value = CalculateDamage(value, is_enemy);
        if ( IsCrit(is_enemy) ) {
          value = value * 150 / 100;
          IO::PrintBattleCrit();
        }
        if ( is_enemy ) {
          dogdoing.MinusHp(value);
          IO::PrintBattleDamage(enemy.GetName(), dogdoing.GetName(), value);
          IO::PrintBattleHpInfo(dogdoing.GetCreatureInfo());
        } else {
          enemy.MinusHp(value);
          IO::PrintBattleDamage(dogdoing.GetName(), enemy.GetName(), value);
          IO::PrintBattleHpInfo(enemy.GetCreatureInfo());
        }
      } else {
        IO::PrintBattleDoesNotHit();
      }
    } else if ( effect == SkillEffect::Heal ) {
      if ( is_enemy ) {
        enemy.Heal(value);
        IO::PrintBattleHeal(enemy.GetName(), value);
        IO::PrintBattleHpInfo(enemy.GetCreatureInfo());
      } else {
        dogdoing.Heal(value);
        IO::PrintBattleHeal(dogdoing.GetName(), value);
        IO::PrintBattleHpInfo(dogdoing.GetCreatureInfo());
      }
    } else if ( effect == SkillEffect::Defend ) {

    } else if ( effect == SkillEffect::Buff ) {

    }
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

void Battle::SetElementBonus() {
  Element dd_element = dogdoing.GetElement();
  Element enemy_element = enemy.GetElement();
  if ( dd_element == Element::Dark && enemy_element == Element::Water ) {
    damage_increase_of_dd += 20;
    damage_increase_of_enemy -= 20;
    is_advantage = 1;
  } else if ( dd_element == Element::Water && enemy_element == Element::Fire ) {
    damage_increase_of_dd += 20;
    damage_increase_of_enemy -= 20;
    is_advantage = 1;
  } else if ( dd_element == Element::Fire && enemy_element == Element::Grass ) {
    damage_increase_of_dd += 20;
    damage_increase_of_enemy -= 20;
    is_advantage = 1;
  } else if ( dd_element == Element::Grass && enemy_element == Element::Thunder ) {
    damage_increase_of_dd += 20;
    damage_increase_of_enemy -= 20;
    is_advantage = 1;
  } else if ( dd_element == Element::Thunder && enemy_element == Element::Dark ) {
    damage_increase_of_dd += 20;
    damage_increase_of_enemy -= 20;
    is_advantage = 1;
  }

  if ( enemy_element == Element::Dark && dd_element == Element::Water ) {
    damage_increase_of_dd -= 20;
    damage_increase_of_enemy += 20;
    is_advantage = 2;
  } else if ( enemy_element == Element::Water && dd_element == Element::Fire ) {
    damage_increase_of_dd -= 20;
    damage_increase_of_enemy += 20;
    is_advantage = 2;
  } else if ( enemy_element == Element::Fire && dd_element == Element::Grass ) {
    damage_increase_of_dd -= 20;
   damage_increase_of_enemy += 20;
   is_advantage = 2;
  } else if ( enemy_element == Element::Grass && dd_element == Element::Thunder ) {
    damage_increase_of_dd -= 20;
    damage_increase_of_enemy += 20;
    is_advantage = 2;
  } else if ( enemy_element == Element::Thunder && dd_element == Element::Dark ) {
    damage_increase_of_dd -= 20;
    damage_increase_of_enemy += 20;
    is_advantage = 2;
  }
}
