#ifndef SKILL_H
#define SKILL_H

#include <string>


enum class SkillType {  // 技能類型
  None, Normal, Skill, Ult
};

enum class SkillEffect {    // 技能效果
  None, Attack, Heal, Defend, Buff
};

enum class SkillID {
  None, NormalAttack, Heal
};

struct SkillInfo{
  std::string skill_name;
  SkillType skill_type;
  std::string skill_info;
  SkillEffect skill_effect;
  int value;
  SkillID id;
  int cd;
};

struct SkillDetail {
  SkillEffect effect;
  int value;
  std::string name;
};

class SkillDataBase {
public:
  static SkillInfo GetSkillInfo(SkillID id, int atk);
  static SkillDetail GetSkillDetail(SkillInfo skill);
};




#endif