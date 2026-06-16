#include <iostream>
#include "../include/Battle.h"

#include "../include/DogDoing.h"
#include "../include/Creature.h"
#include "../include/User.h"
#include "../include/Random.h"
#include "../include/IO.h"
#include "../include/skill.h"

Battle::Battle(User& user, DogDoing& dogdoing, Enemy& enemy)
    : user(user), dogdoing(dogdoing), enemy(enemy) {
  SetElementBonus();
  SetBattleTempValue(true);
  SetBattleTempValue(false);
  
}
void Battle::SetBattleTempValue(bool is_enemy) {
  if ( is_enemy ) {
    enemy_value.base_attack = enemy.GetATK();
    enemy_value.base_hp = enemy.GetHp();
    enemy_value.base_max_hp = enemy.GetMaxHp();
    enemy_value.base_speed = enemy.GetSpeed();
    enemy_value.base_crit_rate = enemy.GetCritRate();
    enemy_value.base_hit_rate = enemy.GetHitRate();
    enemy_value.base_dodge_rate = enemy.GetDodgeRate();
  } else {
    dd_value.base_attack = dogdoing.GetATK();
    dd_value.base_hp = dogdoing.GetHp();
    dd_value.base_max_hp = dogdoing.GetMaxHp();
    dd_value.base_speed = dogdoing.GetSpeed();
    dd_value.base_crit_rate = dogdoing.GetCritRate();
    dd_value.base_hit_rate = dogdoing.GetHitRate();
    dd_value.base_dodge_rate = dogdoing.GetDodgeRate();
    
  }
}

CreatureInfo Battle::GetBattleCreatureInfo(bool is_enemy) {
  if (is_enemy) {
    return{
      enemy.GetHp() + enemy_value.temp_hp,
      enemy_value.base_max_hp + enemy_value.temp_max_hp,
      enemy_value.base_attack + enemy_value.temp_attack,
      enemy_value.base_speed + enemy_value.temp_speed,
      enemy.GetName(),
      enemy.GetElement(),
      0,
      0,
      enemy.GetNumOfSkill()
    };
  } else {
    return{
      dogdoing.GetHp() + dd_value.temp_hp,
      dd_value.base_max_hp + dd_value.temp_max_hp,
      dd_value.base_attack + dd_value.temp_attack,
      dd_value.base_speed + dd_value.temp_speed,
      dogdoing.GetName(),
      dogdoing.GetElement(),
      0,
      0,
      dogdoing.GetNumOfSkill()
    };
  }
}
bool Battle::IsCrit(bool is_enemy) {
  int crit_rate = 0;
  if ( is_enemy ) {
    crit_rate = enemy_value.base_crit_rate + enemy_value.temp_crit_rate;
  } else {
    crit_rate = dd_value.base_crit_rate + dd_value.temp_crit_rate;
  }
  return Random::RandomChance(crit_rate);
}

bool Battle::IsHit(bool is_enemy) {
  SetOverHit(is_enemy, 0);
  int attacker_hit, defender_dodge;  // 攻擊方, 被攻擊方
  if ( is_enemy ) {
    attacker_hit = enemy_value.base_hit_rate + enemy_value.temp_hit_rate;
    defender_dodge = dd_value.base_dodge_rate + dd_value.temp_dodge_rate;
  } else {
    attacker_hit = dd_value.base_hit_rate + dd_value.temp_hit_rate;
    defender_dodge = enemy_value.base_dodge_rate + enemy_value.temp_dodge_rate;
  }

  int hit_rate = attacker_hit - defender_dodge;

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
    dd_value.over_hit = over_hit;
  } else {
    enemy_value.over_hit = over_hit;
  }
}

int Battle::CalculateDamage(int damage, bool is_enemy) {
  int final_damage = 0;
  if ( is_enemy ) {
    final_damage = damage;
    int damage_increase = enemy_value.base_damage_increase + enemy_value.temp_damage_increase;
    int defend = dd_value.base_defend + dd_value.temp_defend;
    final_damage = (final_damage + enemy_value.over_hit) * (100 + damage_increase - defend) / 100;
    SetOverHit(is_enemy, 0);
    return final_damage;
  }

  final_damage = damage;
  int damage_increase = dd_value.base_damage_increase + dd_value.temp_damage_increase;
  int defend = enemy_value.base_defend + enemy_value.temp_defend;
  final_damage = (final_damage + dd_value.over_hit ) * (100 + damage_increase - defend ) / 100;
  SetOverHit(is_enemy, 0);
  return final_damage;
}

int Battle::BattleHeal(bool is_enemy, int heal) {
  int now_hp = 0;
  int max_hp = 0;
  if ( is_enemy ) {
    now_hp = enemy.GetHp();
    max_hp = enemy_value.base_max_hp + enemy_value.temp_max_hp;
  } else {
    now_hp = dogdoing.GetHp();
    max_hp = dd_value.base_max_hp + dd_value.temp_max_hp;
  }

  int new_hp = now_hp + heal;
  if ( new_hp > max_hp ) {
    new_hp = max_hp;
  }
  if ( new_hp < 0 ) {
    new_hp = 0;
  }

  if ( is_enemy ) {
    enemy.SetHp(new_hp);
  } else {
    dogdoing.SetHp(new_hp);
  }
  return new_hp - now_hp;
}

void Battle::ClampBattleHp(bool is_enemy) {
  int max_hp = 0;
  if ( is_enemy ) {
    max_hp = enemy_value.base_max_hp + enemy_value.temp_max_hp;
    if ( enemy.GetHp() > max_hp ) {
      enemy.SetHp(max_hp);
    }
  } else {
    max_hp = dd_value.base_max_hp + dd_value.temp_max_hp;
    if ( dogdoing.GetHp() > max_hp ) {
      dogdoing.SetHp(max_hp);
    }
  }
}

void Battle::Run() {
  IO::PrintBattleStart(dogdoing.GetName(), enemy.GetName(), is_advantage);

  IO::PrintDot(1);
  IO::PrintBattleHpInfo(dogdoing.GetCreatureInfo());
  IO::PrintBattleHpInfo(enemy.GetCreatureInfo());
  IO::PrintDot(1);
  while ( IsBattleOver() == false && game_run == true) {
    dd_value.action_value += (dd_value.base_speed + dd_value.temp_speed);
    enemy_value.action_value += (enemy_value.base_speed + enemy_value.temp_speed);

    if ( dd_value.action_value >= 1000 && enemy_value.action_value >= 1000 ) {
      if ( dd_value.action_value >= enemy_value.action_value ) {
        DDTurn();
        dd_value.action_value -= 1000;
        if ( IsBattleOver() == false && game_run == true ) {
          EnemyTurn();
          enemy_value.action_value -= 1000;
        }
      } else {
        EnemyTurn();
        enemy_value.action_value -= 1000;
        if ( IsBattleOver() == false && game_run == true ) {
          DDTurn();
          dd_value.action_value -= 1000;
        }
      }
      continue;
    } 

    if ( dd_value.action_value >= 1000 ) {
      DDTurn();
      dd_value.action_value -= 1000;
    }

    if (enemy_value.action_value >= 1000 ) {
      EnemyTurn();
      enemy_value.action_value -= 1000;
    }

  }
  IO::Pause(1);
  IO::PrintBattleEnd();
  dogdoing.ResetSkillCD();
  enemy.ResetSkillCD();
  if ( dogdoing.GetHp() <= 0 || game_run == false  ) {
    dogdoing.SetHp(0);
    IO::PrintBattleLose();
  } else {
    IO::PrintBattleWin();
    Win();
  }
}

void Battle::Win() {
  dogdoing.AddExp(enemy.GetExpReward());
  user.AddCoin(enemy.GetCoinReward());
  IO::PrintUserGetCoin(user.GetUserName(), enemy.GetCoinReward());
}



enum class BattleOperate{
  Battle, Unknown, Help, Info, Quit, Attack, ListSkill, EnemyInfo, QuitCheck,
  QuitCancel, QuitConfirm, QuitHelp
};

std::string Battle::ToLower(std::string str) {
  for ( char& c : str ) {
    c = tolower(c);
  }
  return str;
}


BattleOperate  Battle::GetOp(std::string op) {
  op = ToLower(op);
  if ( control == BattleControl::Battle ) {
    if ( IsDigit(op) ) {
      select_skill = std::stoi(op);
      return BattleOperate::Attack;
    } 
    if ( op == "h" || op ==  "help" ) {
      return BattleOperate::Help;
    }
    if ( op == "i" || op == "info" ) {
      return BattleOperate::Info;
    }
    if ( op == "l" || op == "list" ) {
      return BattleOperate::ListSkill;
    }
    if ( op == "q" || op == "quit" ) {
      return BattleOperate::Quit;
    }
    if ( op == "e" || op == "enemy" ) {
      return BattleOperate::EnemyInfo;
    }
  } else if ( control == BattleControl::Quit ) {
    if ( op == "h" || op == "help" ) {
      return BattleOperate::QuitHelp;
    } else if ( op == "y" || op == "yes" ) {
      return BattleOperate::QuitConfirm;
    } else if ( op == "n" || op == "no" ) {
      return BattleOperate::QuitCancel;
    }
  }
  return BattleOperate::Unknown;
}
void Battle::DDTurn(bool bonus_turn) {
  IO::Pause(1);
  std::string str;
  IO::PrintBattleRoundStart(dogdoing.GetName());
  while ( game_run != false ) {
    IO::PrintOperateWating();
    IO::GetToken(str);
    BattleOperate op = GetOp(str);
    if ( control == BattleControl::Battle ) {
      if ( op == BattleOperate::Attack ) {
        SkillID skill_id = dogdoing.GetIndexOfSkillList(select_skill);

        if ( skill_id == SkillID::None ) {
          IO::PrintSkillSelectError();
          continue;
        } else {
          if ( dogdoing.CanUseSkill(select_skill) ) {
            dogdoing.ReSetSkillCD(select_skill);
            select_skill = -1;
            SkillInfo skill_info = SkillDataBase::GetSkillInfo(skill_id);
            SkillEffectApply(false, skill_info);
            return;
          } else {
            IO::PrintSkillUnready();
          }
        }
      } else if ( op == BattleOperate::Help ) {
        IO::PrintBattleHelp();
      } else if ( op == BattleOperate::ListSkill ) {
        dogdoing.ListSkill();
        IO::CreatureListBuff(dd_buff);
      } else if ( op == BattleOperate::Info ) {
        IO::PrintBattleInfo(GetBattleCreatureInfo(false));
        dogdoing.ListSkill();
        IO::CreatureListBuff(dd_buff);
      } else if ( op == BattleOperate::Quit ) {
        IO::BattleQuitCheck();
        control = BattleControl::Quit;
      } else if ( op == BattleOperate::EnemyInfo ) {
        IO::PrintBattleInfo(GetBattleCreatureInfo(true));
        enemy.ListSkill();
        IO::CreatureListBuff(enemy_buff);
      } else if ( op == BattleOperate::Unknown ) {
        IO::PrintInputError(str);
      }
    } else if ( control == BattleControl::Quit ) {
      if ( op == BattleOperate::QuitCancel ) {
        IO::BattleQuitCancel();
        control = BattleControl::Battle;
      } else if ( op == BattleOperate::QuitConfirm ) {
        IO::BattleQuit();
        game_run = false;
      } else if ( op == BattleOperate::QuitHelp ) {
        IO::BattleQuitHelp();
      }
    }
    
  }
  IO::Pause(1);
  if ( bonus_turn == false ) {
    dogdoing.ReduceSkillCD();
    ReduceBuffRound(false);
  }
}

void Battle::EnemyTurn(bool bonus_turn) {
  IO::PrintBattleRoundStart(enemy.GetName());
  int use_skill = 1;
  SkillID skill_id = SkillID::None;
  IO::Pause(1);
  if ( enemy.GetNumOfSkill() > 1 ) {
    use_skill = Random::RandomInt(2, enemy.GetNumOfSkill());
    int try_count = 0;
    while ( EnemyShouldUseSkill(use_skill) == false && try_count < 20 ) {
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
  SkillInfo skill_info = SkillDataBase::GetSkillInfo(skill_id);
  enemy.ReSetSkillCD(use_skill);
  SkillEffectApply(true, skill_info);
  if ( bonus_turn == false ) {
    enemy.ReduceSkillCD();
    ReduceBuffRound(true);
  }
}

bool Battle::EnemyShouldUseSkill(int index) {
  if ( enemy.CanUseSkill(index) == false ) {
    return false;
  }

  SkillID skill_id = enemy.GetIndexOfSkillList(index);
  SkillInfo skill_info = SkillDataBase::GetSkillInfo(skill_id);
  int hp = enemy.GetHp() + enemy_value.temp_hp;
  int max_hp = enemy_value.base_max_hp + enemy_value.temp_max_hp;
  if ( skill_info.main_use == SkillEffect::Heal &&hp * 100 / max_hp > 80 ) {
    return false;
  }

  return true;
}

void Battle::ApplyBuff(bool is_enemy, std::vector<BuffInfo> buff) {
  int n = buff.size();
  for ( int i = 0; i < n; i++ ) {
    if ( buff[i].buff_type == BattleBuffType::NoBuff ) {
      continue;
    }

    bool same_buff = false;

    // 處理相同buff不應該疊加，而是延長時間
    if ( is_enemy ) {
      for ( BuffInfo& buff_info :  enemy_buff ) {        
        if ( buff_info.buff_name == buff[i].buff_name ) {
          buff_info.round = buff[i].round;
          same_buff = true;
          continue;
        }
      }
    }
    else {
      for ( BuffInfo& buff_info : dd_buff ) {
        if ( buff_info.buff_name == buff[i].buff_name ) {
          buff_info.round = buff[i].round;
          same_buff = true;
          continue;
        }
      }
    }
    if ( same_buff ) {
      continue;;
    }
    
    if ( is_enemy ) {
      enemy_buff.push_back(buff[i]);
    } else {
      dd_buff.push_back(buff[i]);
    }

    if ( buff[i].buff_type == BattleBuffType::AddAttack ) {
      if ( is_enemy ) {
        enemy_value.temp_attack += buff[i].value;
      } else {
        dd_value.temp_attack += buff[i].value;
      }
    } else if ( buff[i].buff_type == BattleBuffType::AddCritRate ) {
      if ( is_enemy ) {
        enemy_value.temp_crit_rate += buff[i].value;
      } else {
        dd_value.temp_crit_rate += buff[i].value;
      }
    } else if ( buff[i].buff_type == BattleBuffType::AddDamageIncrease ) {
      if ( is_enemy ) {
        enemy_value.temp_damage_increase += buff[i].value;
      } else {
        dd_value.temp_damage_increase += buff[i].value;
      }
    } else if ( buff[i].buff_type == BattleBuffType::AddDefend ) {
      if ( is_enemy ) {
        enemy_value.temp_defend += buff[i].value;
      } else {
        dd_value.temp_defend += buff[i].value;
      }
    } else if ( buff[i].buff_type == BattleBuffType::AddDodgeRate ) {
      if ( is_enemy ) {
        enemy_value.temp_dodge_rate += buff[i].value;
      } else {
        dd_value.temp_dodge_rate += buff[i].value;
      }

    } else if ( buff[i].buff_type == BattleBuffType::AddHitRate ) {
      if ( is_enemy ) {
        enemy_value.temp_hit_rate += buff[i].value;
      } else {
        dd_value.temp_hit_rate += buff[i].value;
      }
    } else if ( buff[i].buff_type == BattleBuffType::AddHp ) {
      if ( is_enemy ) {
        enemy_value.temp_hp += buff[i].value;
      } else {
        dd_value.temp_hp += buff[i].value;
      }
    } else if ( buff[i].buff_type == BattleBuffType::AddMaxHp ) {
      if ( is_enemy ) {
        enemy_value.temp_max_hp += buff[i].value;
      } else {
        dd_value.temp_max_hp += buff[i].value;
      }       
    } else if ( buff[i].buff_type == BattleBuffType::AddSpeed ) {
      if ( is_enemy ) {
        enemy_value.temp_speed += buff[i].value;
      } else {
        dd_value.temp_speed += buff[i].value;
      }
    } else if ( buff[i].buff_type == BattleBuffType::AddMaxHpPercent ) {
      if ( is_enemy ) {
        enemy_value.temp_max_hp += buff[i].value * enemy_value.base_max_hp / 100;
      }
      else {
        dd_value.temp_max_hp += buff[i].value * dd_value.base_max_hp / 100;        
      }
    }
 
  }
}

void Battle::ApplyEraseBuff(bool is_enemy, BuffInfo erase_buff) {
  if ( erase_buff.buff_type == BattleBuffType::NoBuff ) {
    return;
  } else if ( erase_buff.buff_type == BattleBuffType::AddAttack ) {
      if ( is_enemy ) {
        enemy_value.temp_attack -= erase_buff.value;
      } else {
        dd_value.temp_attack -= erase_buff.value;
      }
  } else if ( erase_buff.buff_type == BattleBuffType::AddCritRate ) {
      if ( is_enemy ) {
        enemy_value.temp_crit_rate -= erase_buff.value;
      } else {
        dd_value.temp_crit_rate -= erase_buff.value;
      }  
  } else if ( erase_buff.buff_type == BattleBuffType::AddDamageIncrease ) {
      if ( is_enemy ) {
        enemy_value.temp_damage_increase -= erase_buff.value;
      } else {
        dd_value.temp_damage_increase -= erase_buff.value;
      }     
  } else if ( erase_buff.buff_type == BattleBuffType::AddDefend ) {
      if ( is_enemy ) {
        enemy_value.temp_defend -= erase_buff.value;
      } else {
        dd_value.temp_defend -= erase_buff.value;
      }    
  } else if ( erase_buff.buff_type == BattleBuffType::AddDodgeRate ) {
      if ( is_enemy ) {
        enemy_value.temp_dodge_rate -= erase_buff.value;
      } else {
        dd_value.temp_dodge_rate -= erase_buff.value;
      }  
  } else if ( erase_buff.buff_type == BattleBuffType::AddHitRate ) {
      if ( is_enemy ) {
        enemy_value.temp_hit_rate -= erase_buff.value;
      } else {
        dd_value.temp_hit_rate -= erase_buff.value;
      }  
  } else if ( erase_buff.buff_type == BattleBuffType::AddHp ) {
      if ( is_enemy ) {
        enemy_value.temp_hp -= erase_buff.value;
      } else {
        dd_value.temp_hp -= erase_buff.value;
      }    
  } else if ( erase_buff.buff_type == BattleBuffType::AddMaxHp ) {
      if ( is_enemy ) {
        enemy_value.temp_max_hp -= erase_buff.value;
      } else {
        dd_value.temp_max_hp -= erase_buff.value;
      }
      ClampBattleHp(is_enemy);
  } else if ( erase_buff.buff_type == BattleBuffType::AddSpeed ) {
      if ( is_enemy ) {
        enemy_value.temp_speed -= erase_buff.value;
      } else {
        dd_value.temp_speed -= erase_buff.value;
      }    
  } else if ( erase_buff.buff_type == BattleBuffType::AddMaxHpPercent ) {
    if ( is_enemy ) {
      enemy_value.temp_max_hp -= erase_buff.value * enemy_value.base_max_hp / 100;
    } else {
      dd_value.temp_max_hp -= erase_buff.value * dd_value.base_max_hp / 100;
    }
    ClampBattleHp(is_enemy);
  }
}
void Battle::ReduceBuffRound(bool is_enemy) {
  if ( is_enemy ) {
    int n = enemy_buff.size();
    std::vector<int> erase_buff;
    for ( int i = 0; i < n; i++ ) {
      enemy_buff[i].round -= 1;
      if ( enemy_buff[i].round < 0 ) {
        erase_buff.push_back(i);
      }
    }
    n = erase_buff.size();
    for ( int i = n - 1; i >= 0; i--  ) {
      ApplyEraseBuff(is_enemy, enemy_buff[erase_buff[i]]);
      enemy_buff.erase(enemy_buff.begin() + erase_buff[i]);
    }
  } else {
    int n = dd_buff.size();
    std::vector<int> erase_buff;
    for ( int i = 0; i < n; i++ ) {
      dd_buff[i].round -= 1;
      if ( dd_buff[i].round < 0 ) {
        erase_buff.push_back(i);
      }
    }
    n = erase_buff.size();
    for ( int i = n - 1; i >= 0; i--  ) {
      ApplyEraseBuff(is_enemy, dd_buff[erase_buff[i]]);
      dd_buff.erase(dd_buff.begin() + erase_buff[i]);
    }    
  }
}
bool Battle::IsBattleOver() const {
  return dogdoing.GetHp() <= 0 || enemy.GetHp() <= 0;
}

int Battle::CalculateSkillValue(bool is_enemy, SkillDetail skill_detail) {
  if ( skill_detail.value_type == SkillValueType::Fixed ) {
    return skill_detail.value;
  }

  if ( skill_detail.value_type == SkillValueType::AtkPercent ) {
    if ( is_enemy ) {
      int attack = enemy_value.base_attack + enemy_value.temp_attack;
      return attack * skill_detail.value / 100;
    }
    int attack = dd_value.base_attack + dd_value.temp_attack;
    return attack * skill_detail.value / 100;
  }

  if ( skill_detail.value_type == SkillValueType::MaxHpPercent ) {
    if ( is_enemy ) {
      int max_hp = enemy_value.base_max_hp + enemy_value.temp_max_hp;
      return max_hp * skill_detail.value / 100;
    }
    int max_hp = dd_value.base_max_hp + dd_value.temp_max_hp;
    return max_hp * skill_detail.value / 100;
  }

  if ( skill_detail.value_type == SkillValueType::CurrentHpPercent ) {
    if ( is_enemy ) {
      int hp = enemy.GetHp() + enemy_value.temp_hp;
      return hp * skill_detail.value / 100;
    }
    int hp = dogdoing.GetHp() + dd_value.temp_hp;
    return hp * skill_detail.value / 100;
  }

  if ( skill_detail.value_type == SkillValueType::LostHpPercent ) {
    if ( is_enemy ) {
      int max_hp =  enemy_value.base_max_hp + enemy_value.temp_max_hp;
      int hp = enemy.GetHp() + enemy_value.temp_hp;
      int lose_hp = max_hp - hp;
      return lose_hp * skill_detail.value / 100;
    }
    int max_hp =  dd_value.base_max_hp + dd_value.temp_max_hp;
    int hp = dogdoing.GetHp() + dd_value.temp_hp;
    int lose_hp = max_hp - hp;
    return lose_hp * skill_detail.value / 100;
  }
  if (skill_detail.value_type == SkillValueType::Damage ) {
    return skill_detail.value;
  }

  return skill_detail.value;
}

void Battle::SkillEffectApply(bool is_enemy, SkillInfo skill_info) {
  int n = skill_info.skill_detail.size();
  IO::Pause(1);
  bool hit = true;
  int last_attack_damage = 0;
  SkillResult result;
  result.skill_name = skill_info.skill_name;

  for ( int i = 0; i < n; i++ ) {             //   處理技能效果
    SkillDetail skill_detail = skill_info.skill_detail[i];
    int value = CalculateSkillValue(is_enemy, skill_detail);
    SkillEffect effect = skill_detail.effect;
    if ( hit == false && skill_detail.control == SkillControl::AttackHit ) {  // 處理需要命中才生效的技能
      continue;
    }
    IO::Pause(1);
    if ( effect == SkillEffect::Attack ) {
      if ( IsHit(is_enemy) ) {
        hit = true;
        bool is_crit = false;
        value = CalculateDamage(value, is_enemy);
        if ( IsCrit(is_enemy) ) {
          value = value * 150 / 100;
          is_crit = true;
        }
        last_attack_damage = value;
        if ( is_enemy ) {
          dogdoing.MinusHp(value);
        } else {
          enemy.MinusHp(value);
        }
        result.details.push_back({effect, value, true, is_crit});
      } else {
        hit = false;
        last_attack_damage = 0;
        result.details.push_back({effect, 0, false});
      }
    } else if ( effect == SkillEffect::Heal ) {
      if ( skill_detail.value_type == SkillValueType::Damage ) {
        value = last_attack_damage * CalculateSkillValue(is_enemy, skill_detail) / 100;
      }
      value = BattleHeal(is_enemy, value);
      result.details.push_back({effect, value, true});
    } else if ( effect == SkillEffect::Defend ) {

    } else if ( effect == SkillEffect::Buff ) {
      int buff_count = skill_info.buff_info.size();
      for ( int j = 0; j < buff_count; j++ ) {
        BuffInfo buff_info = skill_info.buff_info[j];
        if ( buff_info.buff_type == BattleBuffType::NoBuff ) {
          continue;
        }
        if ( buff_info.target == BuffTarget::Self ) {
          ApplyBuff(is_enemy, {buff_info});
        } else if ( buff_info.target == BuffTarget::Opponent ) {
          ApplyBuff(!is_enemy, {buff_info});
        }

        if ( buff_info.buff_name != "" ) {
          result.details.push_back({
            effect,
            0,
            true,
            false,
            buff_info.buff_name
          });
        }
      }
    }
  }

  if ( is_enemy ) {
    IO::PrintSkillResult(enemy.GetName(), dogdoing.GetName(), result);
  } else {
    IO::PrintSkillResult(dogdoing.GetName(), enemy.GetName(), result);
  }
  IO::PrintBattleHpInfo(GetBattleCreatureInfo(false));
  IO::PrintBattleHpInfo(GetBattleCreatureInfo(true));
}

bool Battle::IsDigit(std::string str)  {
  for ( char c : str ) {
    if ( !isdigit(c) ) {
      return false;
    }
  }
  return true;
}

void Battle::SetElementBonus() {
  Element dd_element = dogdoing.GetElement();
  Element enemy_element = enemy.GetElement();
  if ( dd_element == Element::Dark && enemy_element == Element::Water ) {
    dd_value.temp_damage_increase += 20;
    enemy_value.temp_damage_increase -= 20;
    is_advantage = 1;
  } else if ( dd_element == Element::Water && enemy_element == Element::Fire ) {
    dd_value.temp_damage_increase += 20;
    enemy_value.temp_damage_increase -= 20;
    is_advantage = 1;
  } else if ( dd_element == Element::Fire && enemy_element == Element::Grass ) {
    dd_value.temp_damage_increase += 20;
    enemy_value.temp_damage_increase -= 20;
    is_advantage = 1;
  } else if ( dd_element == Element::Grass && enemy_element == Element::Thunder ) {
    dd_value.temp_damage_increase += 20;
    enemy_value.temp_damage_increase -= 20;
    is_advantage = 1;
  } else if ( dd_element == Element::Thunder && enemy_element == Element::Dark ) {
    dd_value.temp_damage_increase += 20;
    enemy_value.temp_damage_increase -= 20;
    is_advantage = 1;
  }

  if ( enemy_element == Element::Dark && dd_element == Element::Water ) {
    dd_value.temp_damage_increase -= 20;
    enemy_value.temp_damage_increase += 20;
    is_advantage = 2;
  } else if ( enemy_element == Element::Water && dd_element == Element::Fire ) {
    dd_value.temp_damage_increase -= 20;
    enemy_value.temp_damage_increase += 20;
    is_advantage = 2;
  } else if ( enemy_element == Element::Fire && dd_element == Element::Grass ) {
    dd_value.temp_damage_increase -= 20;
    enemy_value.temp_damage_increase += 20;
   is_advantage = 2;
  } else if ( enemy_element == Element::Grass && dd_element == Element::Thunder ) {
    dd_value.temp_damage_increase -= 20;
    enemy_value.temp_damage_increase += 20;
    is_advantage = 2;
  } else if ( enemy_element == Element::Thunder && dd_element == Element::Dark ) {
    dd_value.temp_damage_increase -= 20;
    enemy_value.temp_damage_increase += 20;
    is_advantage = 2;
  }
}
