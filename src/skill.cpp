#include "../include/skill.h"

SkillInfo SkillDataBase::GetSkillInfo(SkillID id) {
  if (id == SkillID::None ) {
    return{
      "沒有技能",
      "無",
      SkillEffect::None,
      0,
      {{SkillEffect::None, 0, SkillControl::None}},
      {{BattleBuffType::NoBuff, "", 0, 0}}
    };
  } else if ( id == SkillID::NormalAttack ) {
    return{
      "普通攻擊",
      "造成攻擊力 100% 的傷害",
      SkillEffect::Attack,
      0,
      {{SkillEffect::Attack, 100, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, "", 0, 0}}
    };
  } else if ( id == SkillID::Heal ) {
    return{
      "治癒",
      "回復攻擊力 80% 的生命",
      SkillEffect::Heal,
      2,
      {{SkillEffect::Heal, 80, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, "", 0, 0}}
    };
  } else if ( id == SkillID::Slime_Attack ) {
    return {
      "粘液攻擊",
      "造成攻擊力 150% 的傷害",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, 150, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, "", 0, 0}}
    };
  } else if ( id == SkillID::Goblin_Bash ) {
    return {
      "重擊",
      "造成攻擊力 120% 的傷害",
      SkillEffect::Attack,
      2,
      {{SkillEffect::Attack, 120, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, "", 0, 0}}
    };
  } else if ( id == SkillID::Goblin_Stab ) {
    return {
      "刺擊",
      "造成攻擊力 150% 的傷害",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, 150, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, "", 0, 0}}
    };
  } else if ( id == SkillID::Goblin_SneakAttack ) {
    return {
      "偷襲",
      "造成攻擊力 220% 的傷害",
      SkillEffect::Attack,
      5,
      {{SkillEffect::Attack, 220, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, "", 0, 0}}
    };
  } else if ( id == SkillID::Vampire_Drain ) {
    return {
      "吸血攻擊",
      "造成最大生命值 30% 傷害並回復造成的70% 傷害值",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, 30, SkillControl::Always, SkillValueType::MaxHpPercent},
       {SkillEffect::Heal, 70, SkillControl::AttackHit, SkillValueType::Damage}},
      {{BattleBuffType::NoBuff, "", 0, 0}}
    };
  } else if ( id == SkillID::Vampire_BloodLust ) {
    return {
      "貪婪",
      "獲得Buff : 嗜血",
      SkillEffect::Buff,
      5,
      {{SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::AddMaxHpPercent, "嗜血：提升 50% 最大生命值，並獲得 30% 易傷", 3, 50},
       {BattleBuffType::AddDefend, "", 3, -30}}
    };
  } else if ( id == SkillID::Vampire_Normal ) {
    return {
      "普通攻擊",
      "造成最大生命值 20% 的傷害，並回覆造成傷害 50% 的血量",
      SkillEffect::Attack,
      0,
      {{SkillEffect::Attack, 20, SkillControl::Always, SkillValueType::MaxHpPercent},
       {SkillEffect::Heal, 50, SkillControl::AttackHit, SkillValueType::Damage}},
      {{BattleBuffType::NoBuff, "", 0, 0}}
    };
  } else if ( id == SkillID::Vampire_Blood_Mist ) {
    return{
      "血霧",
      "造成最大生命值 35% 的傷害",
      SkillEffect::Attack,
      5,
      {{SkillEffect::Attack, 35, SkillControl::Always, SkillValueType::MaxHpPercent}},
      {{BattleBuffType::NoBuff, "", 0, 0}}      
    };
  }
  return{
      "未知技能",
      "無",
      SkillEffect::None,
      0,
      {{SkillEffect::None , 0, SkillControl::None}},
      {{BattleBuffType::NoBuff, "", 0, 0}}

  };
}
