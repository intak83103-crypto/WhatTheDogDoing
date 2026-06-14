#include "../include/skill.h"

SkillInfo SkillDataBase::GetSkillInfo(SkillID id, int atk) {
  if (id == SkillID::None ) {
    return{
      "沒有技能",
      "無",
      SkillEffect::None,
      0,
      {{SkillEffect::None, 0}}
    };
  } else if ( id == SkillID::NormalAttack ) {
    return{
      "普通攻擊",
      "造成攻擊力100%的傷害",
      SkillEffect::Attack,
      0,
      {{SkillEffect::Attack, atk}}
    };
  } else if ( id == SkillID::Heal ) {
    return{
      "治癒",
      "回復攻擊力80%的生命",
      SkillEffect::Heal,
      2,
      {{SkillEffect::Heal, atk * 80 / 100}}
    };
  } else if ( id == SkillID::Slime_Attack ) {
    return {
      "粘液攻擊",
      "造成攻擊力200%的傷害",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, atk * 200 / 100}}
    };
  } else if ( id == SkillID::Goblin_Bash ) {
    return {
      "重擊",
      "造成攻擊力120%的傷害",
      SkillEffect::Attack,
      2,
      {{SkillEffect::Attack, atk * 120 / 100}}
    };
  } else if ( id == SkillID::Goblin_Stab ) {
    return {
      "刺擊",
      "造成攻擊力150%的傷害",
      SkillEffect::Attack,
      3,
      {{SkillEffect::Attack, atk * 150 / 100}}
    };
  } else if ( id == SkillID::Goblin_SneakAttack ) {
    return {
      "偷襲",
      "造成攻擊力250%的傷害",
      SkillEffect::Attack,
      5,
      {{SkillEffect::Attack, atk * 250 / 100}}
    };
  }
  return{
      "未知技能",
      "無",
      SkillEffect::None,
      0,
      {{SkillEffect::None , 0}}

  };
}
