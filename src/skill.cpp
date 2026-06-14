#include "../include/skill.h"

SkillInfo SkillDataBase::GetSkillInfo(SkillID id, int atk) {
  if (id == SkillID::None ) {
    return{
      "沒有技能",
      SkillType::None,
      "無",
      SkillEffect::None,
      0,
      SkillID::None,
      -1
    };
  } else if ( id == SkillID::NormalAttack ) {
    return{
      "普通攻擊",
      SkillType::Normal,
      "造成攻擊力100%的傷害",
      SkillEffect::Attack,
      atk,
      SkillID::NormalAttack,
      0
    };
  } else if ( id == SkillID::Heal ) {
    return{
      "治癒",
      SkillType::Skill,
      "回復攻擊力80%的生命",
      SkillEffect::Heal,
      atk * 80 / 100,
      id,
      2
    };
  }
  return{
      "未知技能",
      SkillType::None,
      "無",
      SkillEffect::None,
      0,
      SkillID::None,
      -1
  };
}

SkillDetail SkillDataBase::GetSkillDetail(SkillInfo skill) {
  return {skill.skill_effect, skill.value, skill.skill_name};
}

