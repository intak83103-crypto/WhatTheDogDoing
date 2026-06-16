#include "../include/skill.h"

SkillInfo SkillDataBase::GetSkillInfo(SkillID id) {
  if (id == SkillID::None ) {
    return{
      "沒有技能",
      "無",
      SkillEffect::None,
      0,
      {{SkillEffect::None, 0, SkillControl::None}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}
    };
  } else if ( id == SkillID::NormalAttack ) {
    return{
      "普通攻擊",
      "造成攻擊力 100% 的傷害",
      SkillEffect::Attack,
      0,
      {{SkillEffect::Attack, 100, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}
    };
  } else if ( id == SkillID::Heal ) {
    return{
      "治癒",
      "回復攻擊力 80% 的生命",
      SkillEffect::Heal,
      2,
      {{SkillEffect::Heal, 80, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}
    };
  } else if ( id == SkillID::Slime_Attack ) {
    return {
      "粘液攻擊",
      "造成攻擊力 150% 的傷害",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, 150, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}
    };
  } else if ( id == SkillID::Goblin_Bash ) {
    return {
      "重擊",
      "造成攻擊力 120% 的傷害",
      SkillEffect::Attack,
      2,
      {{SkillEffect::Attack, 120, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}
    };
  } else if ( id == SkillID::Goblin_warCry ) {
    return {
      "戰吼",
      "持續三回合：提升基礎攻擊力 30% 的攻擊力",
      SkillEffect::Buff,
      3,
      {{SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::AddAttack, BuffTarget::Self, BuffValueType::Percent,
        "提升基礎攻擊力 30% 的攻擊力", 3, 30}}
    };
  } else if ( id == SkillID::Goblin_SneakAttack ) {
    return {
      "偷襲",
      "造成攻擊力 220% 的傷害",
      SkillEffect::Attack,
      5,
      {{SkillEffect::Attack, 220, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}
    };
  } else if ( id == SkillID::Vampire_Drain ) {
    return {
      "吸血攻擊",
      "造成最大生命值 30% 傷害並回復造成的70% 傷害值",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, 30, SkillControl::Always, SkillValueType::MaxHpPercent},
       {SkillEffect::Heal, 70, SkillControl::AttackHit, SkillValueType::Damage}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}
    };
  } else if ( id == SkillID::Vampire_BloodLust ) {
    return {
      "貪婪",
      "持續三回合 : 嗜血",
      SkillEffect::Buff,
      5,
      {{SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::AddMaxHpPercent, BuffTarget::Self, BuffValueType::Percent,
        "嗜血：提升 50% 最大生命值，並獲得 30% 易傷", 3, 50},
       {BattleBuffType::AddDefend, BuffTarget::Self, BuffValueType::Fixed, "", 3, -30}}
    };
  } else if ( id == SkillID::Vampire_Normal ) {
    return {
      "普通攻擊",
      "造成最大生命值 20% 的傷害，並施加持續三回合 : 淬血 ",
      SkillEffect::Attack,
      0,
      {{SkillEffect::Attack, 20, SkillControl::Always, SkillValueType::MaxHpPercent},
       {SkillEffect::Buff, 0, SkillControl::AttackHit, SkillValueType::Fixed}},
      {{BattleBuffType::DotDamage, BuffTarget::Opponent, BuffValueType::Percent,
        "淬血 : 每回合受到攻擊者最大生命值 8% 的傷害", 3, 8}}
    };
  } else if ( id == SkillID::Vampire_Blood_Mist ) {
    return{
      "血霧",
      "造成最大生命值 35% 的傷害",
      SkillEffect::Attack,
      5,
      {{SkillEffect::Attack, 35, SkillControl::Always, SkillValueType::MaxHpPercent}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}      
    };
  } else if ( id == SkillID::DemonHunter_ExecutionStance ) {
    return {
      "處刑姿態",
      "立即獲得一個額外回合，並且獲得持續三回合 : 狩獵狂熱",
      SkillEffect::Buff,
      5,
      {{SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed},
       {SkillEffect::BonusTurn, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::ExtraTurnOnCrit, BuffTarget::Self, BuffValueType::Fixed, "狩獵狂熱 : 暴擊率 +15% ，如果攻擊造成暴擊，攻擊者會獲得額外回合", 3, 0},
       {BattleBuffType::AddCritRate, BuffTarget::Self, BuffValueType::Fixed, "", 3, 15}}
    };
  } else if ( id == SkillID::DemonHunter_DemonPiercingBolt ) {
    return {
      "破魔箭",
      "造成攻擊力 150% 的傷害",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, 150, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}},      
    }; 
  } else if ( id == SkillID::DemonHunter_HolyPurge ) {
    return {
      "神聖清洗",
      "持續三回合獲得 : 聖裁迅捷、聖水",
      SkillEffect::Buff,
      4,
      {{SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::AddSpeed, BuffTarget::Self, BuffValueType::Fixed, "聖裁迅捷 : 獲得 6 點速度", 3, 6},
       {BattleBuffType::HotHeal, BuffTarget::Self, BuffValueType::Percent, "聖水 : 每回合恢復最大生命值 5% 的血量", 3, 5}}
    };
  }
  return{
      "未知技能",
      "無",
      SkillEffect::None,
      0,
      {{SkillEffect::None , 0, SkillControl::None}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}

  };
}
