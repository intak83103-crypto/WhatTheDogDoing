#include "../include/skill.h"

SkillInfo SkillDataBase::GetSkillInfo(SkillID id, int atk) {
  if (id == SkillID::None ) {
    return{
      "沒有技能",
      "無",
      SkillEffect::None,
      0,
      {{SkillEffect::None, 0, SkillControl::None}}
    };
  } else if ( id == SkillID::NormalAttack ) {
    return{
      "普通攻擊",
      "造成攻擊力 100% 的傷害",
      SkillEffect::Attack,
      0,
      {{SkillEffect::Attack, atk, SkillControl::Always}}
    };
  } else if ( id == SkillID::Heal ) {
    return{
      "治癒",
      "回復攻擊力 80% 的生命",
      SkillEffect::Heal,
      2,
      {{SkillEffect::Heal, atk * 80 / 100, SkillControl::Always}}
    };
  } else if ( id == SkillID::Slime_Attack ) {
    return {
      "粘液攻擊",
      "造成攻擊力 150% 的傷害",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, atk * 200 / 100, SkillControl::Always}}
    };
  } else if ( id == SkillID::Goblin_Bash ) {
    return {
      "重擊",
      "造成攻擊力 120% 的傷害",
      SkillEffect::Attack,
      2,
      {{SkillEffect::Attack, atk * 120 / 100, SkillControl::Always}}
    };
  } else if ( id == SkillID::Goblin_Stab ) {
    return {
      "刺擊",
      "造成攻擊力 150% 的傷害",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, atk * 150 / 100, SkillControl::Always}}
    };
  } else if ( id == SkillID::Goblin_SneakAttack ) {
    return {
      "偷襲",
      "造成攻擊力 220% 的傷害",
      SkillEffect::Attack,
      5,
      {{SkillEffect::Attack, atk * 250 / 100, SkillControl::Always}}
    };
  } else if ( id == SkillID::Vampire_Drain ) {
    return {
      "吸血攻擊",
      "造成攻擊力 150% 傷害並回復造成的傷害值",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, atk * 150 / 100, SkillControl::Always},
       {SkillEffect::Heal, atk * 150 / 100, SkillControl::AttackHit}}   
    };
  } else if ( id == SkillID::Vampire_Claw ) {
    return {
      "血爪",
      "造成攻擊力 200% 傷害",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, atk * 200 / 100, SkillControl::Always}}
    };
  }
  return{
      "未知技能",
      "無",
      SkillEffect::None,
      0,
      {{SkillEffect::None , 0, SkillControl::None}}

  };
}
