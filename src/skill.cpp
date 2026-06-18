#include "../include/skill.h"

#include "../include/Random.h"

namespace {
// 依照稀有度權重抽技能，common_percent / rare_percent 決定抽池機率。
SkillID RandomSkillByRarity(int common_percent, int rare_percent) {
  std::vector<SkillID> common = {
    SkillID::Heal,
    SkillID::QuickSlash,
    SkillID::Regeneration,
    SkillID::IronSkin,
    SkillID::Haste,
    SkillID::PoisonNeedle,
    SkillID::Slime_Attack
  };
  std::vector<SkillID> rare = {
    SkillID::PowerStrike,
    SkillID::GuardBreak,
    SkillID::Focus,
    SkillID::LifeBloom,
    SkillID::ThunderStrike,
    SkillID::Goblin_Bash,
    SkillID::Goblin_warCry
  };
  std::vector<SkillID> epic = {
    SkillID::FlameBurst,
    SkillID::LastStand,
    SkillID::VitalStrike,
    SkillID::Vampire_Drain,
    SkillID::Vampire_BloodLust,
    SkillID::DemonHunter_DemonPiercingBolt,
    SkillID::DemonHunter_HolyPurge
  };

  int roll = Random::RandomInt(1, 100);
  if ( roll <= common_percent ) {
    return common[Random::RandomInt(0, common.size() - 1)];
  }
  if ( roll <= common_percent + rare_percent ) {
    return rare[Random::RandomInt(0, rare.size() - 1)];
  }
  return epic[Random::RandomInt(0, epic.size() - 1)];
}
}

// 技能資料庫：角色只存 SkillID，真正使用時才在這裡查技能內容。
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
  } else if ( id == SkillID::QuickSlash ) {
    return{
      "迅斬",
      "造成攻擊力 130% 的傷害，冷卻很短",
      SkillEffect::Attack,
      1,
      {{SkillEffect::Attack, 130, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}
    };
  } else if ( id == SkillID::PowerStrike ) {
    return{
      "強力斬擊",
      "造成攻擊力 210% 的傷害",
      SkillEffect::Attack,
      4,
      {{SkillEffect::Attack, 210, SkillControl::Always, SkillValueType::AtkPercent}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}
    };
  } else if ( id == SkillID::Regeneration ) {
    return{
      "再生",
      "持續三回合：每回合恢復最大生命值 8%",
      SkillEffect::Buff,
      4,
      {{SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::HotHeal, BuffTarget::Self, BuffValueType::Percent,
        "再生 : 每回合恢復最大生命值 8% 的血量", 3, 8}}
    };
  } else if ( id == SkillID::GuardBreak ) {
    return{
      "破防打擊",
      "造成攻擊力 120% 的傷害，命中後讓敵人三回合受到更多傷害",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, 120, SkillControl::Always, SkillValueType::AtkPercent},
       {SkillEffect::Buff, 0, SkillControl::AttackHit, SkillValueType::Fixed}},
      {{BattleBuffType::AddDefend, BuffTarget::Opponent, BuffValueType::Fixed,
        "破防 : 受到傷害提高 25%", 3, -25}}
    };
  } else if ( id == SkillID::FlameBurst ) {
    return{
      "烈焰爆發",
      "造成攻擊力 190% 的傷害，命中後施加燃燒",
      SkillEffect::Attack,
      5,
      {{SkillEffect::Attack, 190, SkillControl::Always, SkillValueType::AtkPercent},
       {SkillEffect::Buff, 0, SkillControl::AttackHit, SkillValueType::Fixed}},
      {{BattleBuffType::DotDamage, BuffTarget::Opponent, BuffValueType::Percent,
        "燃燒 : 每回合受到攻擊者最大生命值 7% 的傷害", 3, 7}}
    };
  } else if ( id == SkillID::IronSkin ) {
    return{
      "鐵皮",
      "持續三回合：減少 25% 受到的傷害",
      SkillEffect::Buff,
      3,
      {{SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::AddDefend, BuffTarget::Self, BuffValueType::Fixed,
        "鐵皮 : 受到傷害減少 25%", 3, 25}}
    };
  } else if ( id == SkillID::Focus ) {
    return{
      "專注",
      "持續三回合：命中率 +15%，暴擊率 +15%",
      SkillEffect::Buff,
      4,
      {{SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::AddHitRate, BuffTarget::Self, BuffValueType::Fixed,
        "專注 : 命中率 +15%", 3, 15},
       {BattleBuffType::AddCritRate, BuffTarget::Self, BuffValueType::Fixed,
        "專注 : 暴擊率 +15%", 3, 15}}
    };
  } else if ( id == SkillID::Haste ) {
    return{
      "加速",
      "持續三回合：速度 +5",
      SkillEffect::Buff,
      3,
      {{SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::AddSpeed, BuffTarget::Self, BuffValueType::Fixed,
        "加速 : 速度 +5", 3, 5}}
    };
  } else if ( id == SkillID::PoisonNeedle ) {
    return{
      "毒針",
      "造成攻擊力 90% 的傷害，命中後施加中毒",
      SkillEffect::Attack,
      2,
      {{SkillEffect::Attack, 90, SkillControl::Always, SkillValueType::AtkPercent},
       {SkillEffect::Buff, 0, SkillControl::AttackHit, SkillValueType::Fixed}},
      {{BattleBuffType::DotDamage, BuffTarget::Opponent, BuffValueType::Percent,
        "中毒 : 每回合受到攻擊者最大生命值 5% 的傷害", 3, 5}}
    };
  } else if ( id == SkillID::LifeBloom ) {
    return{
      "生命綻放",
      "立即回復攻擊力 70% 的生命，並獲得三回合持續回血",
      SkillEffect::Heal,
      4,
      {{SkillEffect::Heal, 70, SkillControl::Always, SkillValueType::AtkPercent},
       {SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::HotHeal, BuffTarget::Self, BuffValueType::Percent,
        "生命綻放 : 每回合恢復最大生命值 6% 的血量", 3, 6}}
    };
  } else if ( id == SkillID::LastStand ) {
    return{
      "背水一擊",
      "依照自己已損失生命造成 90% 傷害",
      SkillEffect::Attack,
      5,
      {{SkillEffect::Attack, 90, SkillControl::Always,
        SkillValueType::LostHpPercent}},
      {{BattleBuffType::NoBuff, BuffTarget::Self, BuffValueType::Fixed, "", 0, 0}}
    };
  } else if ( id == SkillID::ThunderStrike ) {
    return{
      "雷擊",
      "造成攻擊力 160% 的傷害，並提高命中率",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, 160, SkillControl::Always, SkillValueType::AtkPercent},
       {SkillEffect::Buff, 0, SkillControl::Always, SkillValueType::Fixed}},
      {{BattleBuffType::AddHitRate, BuffTarget::Self, BuffValueType::Fixed,
        "雷感 : 命中率 +10%", 2, 10}}
    };
  } else if ( id == SkillID::VitalStrike ) {
    return{
      "命脈打擊",
      "造成自身最大生命值 25% 的傷害",
      SkillEffect::Attack,
      4,
      {{SkillEffect::Attack, 25, SkillControl::Always,
        SkillValueType::MaxHpPercent}},
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
      "淬血爪擊",
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

// 決定技能稀有度，影響技能庫顯示和技能罐抽取分類。
SkillRarity SkillDataBase::GetSkillRarity(SkillID skill_id) {
  if ( skill_id == SkillID::PowerStrike ||
       skill_id == SkillID::GuardBreak ||
       skill_id == SkillID::Focus ||
       skill_id == SkillID::LifeBloom ||
       skill_id == SkillID::ThunderStrike ||
       skill_id == SkillID::Goblin_Bash ||
       skill_id == SkillID::Goblin_warCry ||
       skill_id == SkillID::Vampire_Blood_Mist ) {
    return SkillRarity::Rare;
  }
  if ( skill_id == SkillID::FlameBurst ||
       skill_id == SkillID::LastStand ||
       skill_id == SkillID::VitalStrike ||
       skill_id == SkillID::Vampire_Drain ||
       skill_id == SkillID::Vampire_BloodLust ||
       skill_id == SkillID::Vampire_Normal ||
       skill_id == SkillID::Goblin_SneakAttack ||
       skill_id == SkillID::DemonHunter_ExecutionStance ||
       skill_id == SkillID::DemonHunter_DemonPiercingBolt ||
       skill_id == SkillID::DemonHunter_HolyPurge ) {
    return SkillRarity::Epic;
  }
  return SkillRarity::Common;
}

std::string SkillDataBase::GetSkillRarityName(SkillID skill_id) {
  SkillRarity rarity = GetSkillRarity(skill_id);
  if ( rarity == SkillRarity::Common ) {
    return "普通";
  }
  if ( rarity == SkillRarity::Rare ) {
    return "稀有";
  }
  return "史詩";
}

std::vector<SkillID> SkillDataBase::GetAllLearnableSkills() {
  // op 指令會使用這份清單一次發放所有可學技能。
  return {
    SkillID::NormalAttack,
    SkillID::Heal,
    SkillID::QuickSlash,
    SkillID::PowerStrike,
    SkillID::Regeneration,
    SkillID::GuardBreak,
    SkillID::FlameBurst,
    SkillID::IronSkin,
    SkillID::Focus,
    SkillID::Haste,
    SkillID::PoisonNeedle,
    SkillID::LifeBloom,
    SkillID::LastStand,
    SkillID::ThunderStrike,
    SkillID::VitalStrike,
    SkillID::Slime_Attack,
    SkillID::Goblin_Bash,
    SkillID::Goblin_warCry,
    SkillID::Goblin_SneakAttack,
    SkillID::Vampire_Normal,
    SkillID::Vampire_Drain,
    SkillID::Vampire_BloodLust,
    SkillID::Vampire_Blood_Mist,
    SkillID::DemonHunter_ExecutionStance,
    SkillID::DemonHunter_DemonPiercingBolt,
    SkillID::DemonHunter_HolyPurge
  };
}

// 技能罐用的抽取池，普通技能機率最高。
SkillID SkillDataBase::GetRandomJarSkill() {
  return RandomSkillByRarity(65, 28);
}

// 保留給等級式掉落使用；目前怪物掉落只掉怪物自己的技能。
SkillID SkillDataBase::GetRandomDropSkill(int enemy_level) {
  if ( enemy_level >= 8 ) {
    return RandomSkillByRarity(45, 38);
  }
  if ( enemy_level >= 5 ) {
    return RandomSkillByRarity(58, 32);
  }
  return RandomSkillByRarity(78, 20);
}
