#include "../include/skill.h"

SkillInfo SkillDataBase::GetSkillInfo(SkillID id) {
  if (id == SkillID::None ) {
    return{
        "沒有技能",
        SkillType::None,
        "無",
        SkillEffect::None,
        0,
        SkillID::None
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
  return {skill.skill_effect, skill.value};
}
