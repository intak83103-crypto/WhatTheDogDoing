#include <iostream>
#include "../include/Battle.h"

#include "../include/DogDoing.h"
#include "../include/Creature.h"
#include "../include/User.h"
#include "../include/Random.h"

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

int Battle::CalculateDamage(bool is_enemy) {
  int final_damage = 0;
  if ( is_enemy ) {
    final_damage = enemy.GetATK();
    final_damage = (final_damage + enemy_over_hit)
        * (100 + enemy.GetDamageIncrease()) / 100;
    SetOverHit(is_enemy, 0);
    return final_damage;
  }

  final_damage = dogdoing.GetATK();
  final_damage = (final_damage + dd_over_hit)
      * (100 + dogdoing.GetDamageIncrease()) / 100;
  SetOverHit(is_enemy, 0);
  return final_damage;
}
