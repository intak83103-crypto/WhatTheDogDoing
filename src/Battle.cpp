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
  // 戰鬥開始前先決定屬性克制，再把雙方原始數值記起來。
  SetElementBonus();
  SetBattleTempValue(true);
  SetBattleTempValue(false);
  
}

// 將戰鬥開始時的基礎能力存起來，Buff 只會改 temp 欄位。
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

// 命中率 = 攻擊方命中 - 防守方閃避；超過 100 的部分會轉成額外傷害。
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

// 暫存溢出的命中率，之後 CalculateDamage 會把它加到傷害裡。
void Battle::SetOverHit(bool is_enemy, int over_hit) {
  if ( is_enemy == false ) {
    dd_value.over_hit = over_hit;
  } else {
    enemy_value.over_hit = over_hit;
  }
}

// 計算最終傷害：基礎傷害會受到增傷、防禦和溢出命中影響。
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

// 實際改變血量並回傳真正回復了多少，避免溢補超過最大生命。
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

// 最大生命被 Buff 移除時，避免目前血量超過新的最大生命。
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

// 戰鬥主迴圈：雙方速度累積行動值，滿 1000 的一方可以行動。
void Battle::Run() {
  IO::PrintBattleStart(dogdoing.GetName(), enemy.GetName(), is_advantage);

  IO::PrintDot(1);
  IO::PrintBattleHpInfo(dogdoing.GetCreatureInfo());
  IO::PrintBattleHpInfo(enemy.GetCreatureInfo());
  IO::PrintDot(1);
  while ( IsBattleOver() == false && game_run == true) {
    dd_value.action_value += (dd_value.base_speed + dd_value.temp_speed);
    enemy_value.action_value += (enemy_value.base_speed + enemy_value.temp_speed);

    // 雙方同時滿行動值時，行動值比較高的人先動。
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

    // 只有刀盾滿行動值時，進入玩家回合。
    if ( dd_value.action_value >= 1000 ) {
      DDTurn();
      dd_value.action_value -= 1000;
    }

    // 只有敵人滿行動值時，進入敵人回合。
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
    // 玩家死亡或主動逃跑，都算戰鬥失敗。
    dogdoing.SetHp(0);
    IO::PrintBattleLose();
  } else {
    IO::PrintBattleWin();
    Win();
  }
}

// 勝利獎勵：經驗和金錢在戰鬥內結算，掉落在 Editor 探索流程結算。
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


// 戰鬥中也有自己的指令解析，和 Editor 主介面分開。
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

// 玩家回合：等待玩家選技能、查看資訊，或確認逃跑。
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
        // 數字代表技能格，先檢查是否有技能、是否冷卻完成。
        SkillID skill_id = dogdoing.GetIndexOfSkillList(select_skill);

        if ( skill_id == SkillID::None ) {
          IO::PrintSkillSelectError();
          continue;
        } else {
          if ( dogdoing.CanUseSkill(select_skill) ) {
            dogdoing.ReSetSkillCD(select_skill);
            select_skill = -1;
            SkillInfo skill_info = SkillDataBase::GetSkillInfo(skill_id);
            bool get_bonus_turn = SkillEffectApply(false, skill_info);
            if ( bonus_turn == false ) {
              // 額外回合不扣冷卻和 Buff 回合，避免額外回合太虧。
              dogdoing.ReduceSkillCD();
              ReduceBuffRound(false);
            }
            if ( get_bonus_turn && IsBattleOver() == false && game_run == true ) {
              // 技能給額外回合時，立刻再跑一次玩家回合。
              DDTurn(true);
            }
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
        // 逃跑需要二次確認，避免輸錯字直接失敗。
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
  if ( bonus_turn == false ) {
    // 如果是被迫離開回合，也要正常結算冷卻和 Buff。
    dogdoing.ReduceSkillCD();
    ReduceBuffRound(false);
  }
}

// 敵人回合：簡單 AI 會隨機選可用技能，不適合時退回普攻。
void Battle::EnemyTurn(bool bonus_turn) {
  IO::PrintBattleRoundStart(enemy.GetName());
  int use_skill = 1;
  SkillID skill_id = SkillID::None;
  if ( enemy.GetNumOfSkill() > 1 ) {
    // 敵人優先從第 2 格以後選技能，第 1 格通常是普攻。
    use_skill = Random::RandomInt(2, enemy.GetNumOfSkill());
    int try_count = 0;
    while ( EnemyShouldUseSkill(use_skill) == false && try_count < 20 ) {
      // 如果技能在冷卻或不適合使用，就重新抽一招。
      use_skill = Random::RandomInt(2, enemy.GetNumOfSkill());
      try_count++;
    }
    if ( EnemyShouldUseSkill(use_skill) == false ) {
      // 多次抽不到合適技能時，退回普通攻擊。
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
  bool get_bonus_turn = SkillEffectApply(true, skill_info);
  if ( bonus_turn == false ) {
    enemy.ReduceSkillCD();
    ReduceBuffRound(true);
  }
  if ( get_bonus_turn && IsBattleOver() == false && game_run == true ) {
    // 敵人如果獲得額外回合，也會立刻再行動。
    EnemyTurn(true);
  }
}

// 敵人 AI 的技能使用條件，例如冷卻中不能用、血太高不浪費補血。
bool Battle::EnemyShouldUseSkill(int index) {
  if ( enemy.CanUseSkill(index) == false ) {
    return false;
  }

  SkillID skill_id = enemy.GetIndexOfSkillList(index);
  SkillInfo skill_info = SkillDataBase::GetSkillInfo(skill_id);
  int hp = enemy.GetHp() + enemy_value.temp_hp;
  int max_hp = enemy_value.base_max_hp + enemy_value.temp_max_hp;
  if ( skill_info.main_use == SkillEffect::Heal &&hp * 100 / max_hp > 80 ) {
    // 血量高於 80% 時，不使用主要用途是治療的技能。
    return false;
  }

  return true;
}

bool Battle::HasBuff(bool is_enemy, BattleBuffType buff_type) {
  if ( is_enemy ) {
    for ( BuffInfo buff_info : enemy_buff ) {
      if ( buff_info.buff_type == buff_type ) {
        return true;
      }
    }
  } else {
    for ( BuffInfo buff_info : dd_buff ) {
      if ( buff_info.buff_type == buff_type ) {
        return true;
      }
    }
  }

  return false;
}

// 將 Buff 設定值轉成實際數值；Percent 會依 Buff 類型抓基礎能力。
int Battle::CalculateBuffValue(bool is_enemy, BuffInfo buff_info) {
  if ( buff_info.value_type == BuffValueType::Fixed ) {
    return buff_info.value;
  }

  if ( buff_info.buff_type == BattleBuffType::AddAttack ) {
    if ( is_enemy ) {
      return enemy_value.base_attack * buff_info.value / 100;
    }
    return dd_value.base_attack * buff_info.value / 100;
  } else if ( buff_info.buff_type == BattleBuffType::AddMaxHp ||
              buff_info.buff_type == BattleBuffType::AddMaxHpPercent ) {
    if ( is_enemy ) {
      return enemy_value.base_max_hp * buff_info.value / 100;
    }
    return dd_value.base_max_hp * buff_info.value / 100;
  } else if ( buff_info.buff_type == BattleBuffType::AddHp ) {
    if ( is_enemy ) {
      return enemy_value.base_max_hp * buff_info.value / 100;
    }
    return dd_value.base_max_hp * buff_info.value / 100;
  } else if ( buff_info.buff_type == BattleBuffType::HotHeal ) {
    if ( is_enemy ) {
      int max_hp = enemy_value.base_max_hp + enemy_value.temp_max_hp;
      return max_hp * buff_info.value / 100;
    }
    int max_hp = dd_value.base_max_hp + dd_value.temp_max_hp;
    return max_hp * buff_info.value / 100;
  } else if ( buff_info.buff_type == BattleBuffType::AddSpeed ) {
    if ( is_enemy ) {
      return enemy_value.base_speed * buff_info.value / 100;
    }
    return dd_value.base_speed * buff_info.value / 100;
  } else if ( buff_info.buff_type == BattleBuffType::AddCritRate ) {
    if ( is_enemy ) {
      return enemy_value.base_crit_rate * buff_info.value / 100;
    }
    return dd_value.base_crit_rate * buff_info.value / 100;
  } else if ( buff_info.buff_type == BattleBuffType::AddHitRate ) {
    if ( is_enemy ) {
      return enemy_value.base_hit_rate * buff_info.value / 100;
    }
    return dd_value.base_hit_rate * buff_info.value / 100;
  } else if ( buff_info.buff_type == BattleBuffType::AddDodgeRate ) {
    if ( is_enemy ) {
      return enemy_value.base_dodge_rate * buff_info.value / 100;
    }
    return dd_value.base_dodge_rate * buff_info.value / 100;
  }

  return buff_info.value;
}

// 套用 Buff：先處理同名刷新，再依 Buff 類型改變暫存能力。
void Battle::ApplyBuff(bool is_enemy, std::vector<BuffInfo> buff) {
  int n = buff.size();
  for ( int i = 0; i < n; i++ ) {
    if ( buff[i].buff_type == BattleBuffType::NoBuff ) {
      continue;
    }

    bool same_buff = false;

    // 同名 Buff 不疊加數值，只刷新持續回合。
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

    buff[i].value = CalculateBuffValue(is_enemy, buff[i]);
    
    // 先把 Buff 存到對應清單，之後回合結束會從清單扣回合。
    if ( is_enemy ) {
      enemy_buff.push_back(buff[i]);
    } else {
      dd_buff.push_back(buff[i]);
    }

    if ( buff[i].buff_type == BattleBuffType::AddAttack ) {
      // 數值型 Buff 會直接加到 temp 欄位，方便之後移除。
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
        enemy_value.temp_max_hp += buff[i].value;
      }
      else {
        dd_value.temp_max_hp += buff[i].value;        
      }
    } else if ( buff[i].buff_type == BattleBuffType::DotDamage ) {
      // DOT 不立刻改能力，等 ReduceBuffRound 時造成傷害。

    } else if ( buff[i].buff_type == BattleBuffType::HotHeal ) {
      // HOT 不立刻改能力，等 ReduceBuffRound 時回血。

    } else if ( buff[i].buff_type == BattleBuffType::ExtraTurnOnCrit ) {
      // 額外回合 Buff 只需要存在清單裡，攻擊暴擊時會檢查。

    }
 
  }
}

// 移除 Buff 時，把 ApplyBuff 加到 temp 的數值扣回來。
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
      enemy_value.temp_max_hp -= erase_buff.value;
    } else {
      dd_value.temp_max_hp -= erase_buff.value;
    }
    ClampBattleHp(is_enemy);
  } else if ( erase_buff.buff_type == BattleBuffType::DotDamage ) {
    // DOT / HOT / 暴擊額外回合沒有改 temp 數值，所以不用扣回。
    return;
  } else if ( erase_buff.buff_type == BattleBuffType::HotHeal ) {
    return;
  } else if ( erase_buff.buff_type == BattleBuffType::ExtraTurnOnCrit ) {
    return;
  }
}

// 回合結束時扣 Buff 回合，並觸發 DOT / HOT。
void Battle::ReduceBuffRound(bool is_enemy) {
  if ( is_enemy ) {
    int n = enemy_buff.size();
    std::vector<int> erase_buff;
    for ( int i = 0; i < n; i++ ) {
      enemy_buff[i].round -= 1;
      if ( enemy_buff[i].buff_type == BattleBuffType::DotDamage ) {
        // DOT：每回合扣血。
        if ( enemy_buff[i].round >= 0 ) {
          enemy.MinusHp(enemy_buff[i].value);
          IO::PrintBuffDamage(enemy.GetName(),
                              enemy_buff[i].buff_name,
                              enemy_buff[i].value);
          IO::PrintBattleHpInfo(GetBattleCreatureInfo(true));
        }
      } else if ( enemy_buff[i].buff_type == BattleBuffType::HotHeal ) {
        // HOT：每回合回血。
        if ( enemy_buff[i].round >= 0 ) {
          int heal = BattleHeal(true, enemy_buff[i].value);
          IO::PrintBuffHeal(enemy.GetName(),
                            enemy_buff[i].buff_name,
                            heal);
          IO::PrintBattleHpInfo(GetBattleCreatureInfo(true));
        }
      }
      if ( enemy_buff[i].round < 0 ) {
        // 回合數結束的 Buff 先記錄 index，迴圈結束後再刪。
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
      if ( dd_buff[i].buff_type == BattleBuffType::DotDamage ) {
        // DOT：每回合扣血。
        if ( dd_buff[i].round >= 0 ) {
          dogdoing.MinusHp(dd_buff[i].value);
          IO::PrintBuffDamage(dogdoing.GetName(),
                              dd_buff[i].buff_name,
                              dd_buff[i].value);
          IO::PrintBattleHpInfo(GetBattleCreatureInfo(false));
        }
      } else if ( dd_buff[i].buff_type == BattleBuffType::HotHeal ) {
        // HOT：每回合回血。
        if ( dd_buff[i].round >= 0 ) {
          int heal = BattleHeal(false, dd_buff[i].value);
          IO::PrintBuffHeal(dogdoing.GetName(),
                            dd_buff[i].buff_name,
                            heal);
          IO::PrintBattleHpInfo(GetBattleCreatureInfo(false));
        }
      }
      if ( dd_buff[i].round < 0 ) {
        // 回合數結束的 Buff 先記錄 index，迴圈結束後再刪。
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

// 技能數值來源不同：固定值、攻擊力百分比、最大生命百分比等。
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

// 結算一個技能的所有 SkillDetail，包含攻擊、治療、Buff 和額外回合。
bool Battle::SkillEffectApply(bool is_enemy, SkillInfo skill_info) {
  int n = skill_info.skill_detail.size();
  IO::Pause(1);
  bool hit = true;
  bool last_attack_crit = false;
  bool get_bonus_turn = false;
  bool bonus_turn_result_added = false;
  int last_attack_damage = 0;
  SkillResult result;
  result.skill_name = skill_info.skill_name;

  for ( int i = 0; i < n; i++ ) {
    SkillDetail skill_detail = skill_info.skill_detail[i];
    int value = CalculateSkillValue(is_enemy, skill_detail);
    SkillEffect effect = skill_detail.effect;
    // AttackHit 代表前一段攻擊命中後，這段效果才會發動。
    if ( hit == false && skill_detail.control == SkillControl::AttackHit ) {
      continue;
    }
    // AttackCrit 代表前一段攻擊暴擊後，這段效果才會發動。
    if ( last_attack_crit == false &&
         skill_detail.control == SkillControl::AttackCrit ) {
      continue;
    }
    IO::Pause(1);
    if ( effect == SkillEffect::Attack ) {
      // 攻擊分支：先判定命中，再算傷害、暴擊和扣血。
      if ( IsHit(is_enemy) ) {
        hit = true;
        bool is_crit = false;
        value = CalculateDamage(value, is_enemy);
        if ( IsCrit(is_enemy) ) {
          value = value * 150 / 100;
          is_crit = true;
        }
        last_attack_crit = is_crit;
        if ( is_crit &&
             HasBuff(is_enemy, BattleBuffType::ExtraTurnOnCrit) ) {
          // 有暴擊額外回合 Buff 時，暴擊會讓使用者再動一次。
          get_bonus_turn = true;
        }
        last_attack_damage = value;
        if ( is_enemy ) {
          dogdoing.MinusHp(value);
        } else {
          enemy.MinusHp(value);
        }
        result.details.push_back({effect, value, true, is_crit});
        if ( get_bonus_turn && bonus_turn_result_added == false ) {
          result.details.push_back({SkillEffect::BonusTurn, 0, true});
          bonus_turn_result_added = true;
        }
      } else {
        hit = false;
        last_attack_crit = false;
        last_attack_damage = 0;
        // 沒命中時，後續 AttackHit 效果不會發動。
        result.details.push_back({effect, 0, false});
      }
    } else if ( effect == SkillEffect::Heal ) {
      // 治療分支：可直接補血，也可依照上一段傷害吸血。
      if ( skill_detail.value_type == SkillValueType::Damage ) {
        value = last_attack_damage * CalculateSkillValue(is_enemy, skill_detail) / 100;
      }
      value = BattleHeal(is_enemy, value);
      result.details.push_back({effect, value, true});
    } else if ( effect == SkillEffect::Defend ) {

    } else if ( effect == SkillEffect::Buff ) {
      // Buff 分支：根據 BuffTarget 決定套在自己或對手身上。
      int buff_count = skill_info.buff_info.size();
      for ( int j = 0; j < buff_count; j++ ) {
        BuffInfo buff_info = skill_info.buff_info[j];
        if ( buff_info.buff_type == BattleBuffType::NoBuff ) {
          continue;
        }
        if ( buff_info.buff_type == BattleBuffType::DotDamage &&
             buff_info.value_type == BuffValueType::Percent ) {
          // DOT 百分比用攻擊者的最大生命先換算成固定傷害。
          if ( is_enemy ) {
            int max_hp = enemy_value.base_max_hp + enemy_value.temp_max_hp;
            buff_info.value = max_hp * buff_info.value / 100;
          } else {
            int max_hp = dd_value.base_max_hp + dd_value.temp_max_hp;
            buff_info.value = max_hp * buff_info.value / 100;
          }
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
    } else if ( effect == SkillEffect::BonusTurn ) {
      // 額外回合分支：只回傳旗標，真正再動在 DDTurn / EnemyTurn 處理。
      get_bonus_turn = true;
      if ( bonus_turn_result_added == false ) {
        result.details.push_back({effect, 0, true});
        bonus_turn_result_added = true;
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
  return get_bonus_turn;
}

bool Battle::IsDigit(std::string str)  {
  for ( char c : str ) {
    if ( !isdigit(c) ) {
      return false;
    }
  }
  return true;
}

// 屬性克制直接用增傷 / 減傷表示，進入戰鬥後不再變動。
void Battle::SetElementBonus() {
  Element dd_element = dogdoing.GetElement();
  Element enemy_element = enemy.GetElement();

  if ( (dd_element == Element::Dark && enemy_element == Element::Light) ||
       (dd_element == Element::Light && enemy_element == Element::Dark) ) {
    // 光暗互剋：雙方都獲得增傷。
    dd_value.temp_damage_increase += 20;
    enemy_value.temp_damage_increase += 20;
    is_advantage = 1;
    return;
  }

  bool dd_advantage = false;
  bool enemy_advantage = false;

  if ( dd_element == Element::Water && enemy_element == Element::Fire ) {
    dd_advantage = true;
  } else if ( dd_element == Element::Fire && enemy_element == Element::Grass ) {
    dd_advantage = true;
  } else if ( dd_element == Element::Grass && enemy_element == Element::Thunder ) {
    dd_advantage = true;
  } else if ( dd_element == Element::Thunder && enemy_element == Element::Water ) {
    dd_advantage = true;
  }

  if ( enemy_element == Element::Water && dd_element == Element::Fire ) {
    enemy_advantage = true;
  } else if ( enemy_element == Element::Fire && dd_element == Element::Grass ) {
    enemy_advantage = true;
  } else if ( enemy_element == Element::Grass && dd_element == Element::Thunder ) {
    enemy_advantage = true;
  } else if ( enemy_element == Element::Thunder && dd_element == Element::Water ) {
    enemy_advantage = true;
  }

  if ( dd_advantage ) {
    // 刀盾克制敵人：刀盾增傷、敵人降傷。
    dd_value.temp_damage_increase += 20;
    enemy_value.temp_damage_increase -= 20;
    is_advantage = 1;
  } else if ( enemy_advantage ) {
    // 敵人克制刀盾：敵人增傷、刀盾降傷。
    dd_value.temp_damage_increase -= 20;
    enemy_value.temp_damage_increase += 20;
    is_advantage = 2;
  }
}
