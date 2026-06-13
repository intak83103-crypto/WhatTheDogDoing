#include "../include/skill.h"

SkillInfo SkillDataBase::GetSkillInfo(SkillID id, int atk) {
  if (id == SkillID::None ) {
    return{
      "沒有技能",
      SkillType::None,
      "無",
      SkillEffect::None,
      0,
      SkillID::None
    };
  } else if ( id == SkillID::NormalAttack ) {
    return{
      "普通攻擊",
      SkillType::Normal,
      "造成攻擊力100%的傷害",
      SkillEffect::Attack,
      atk,
      SkillID::NormalAttack
    };
  }
  return{
      "未知技能",
      SkillType::None,
      "無",
      SkillEffect::None,
      0,
      SkillID::None
  };
}

SkillDetail SkillDataBase::GetSkillDetail(SkillInfo skill) {
  return {skill.skill_effect, skill.value, skill.skill_name};
}
