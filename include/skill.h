#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <vector>

enum class SkillEffect {    // 技能效果
  None, Attack, Heal, Defend, Buff
};

enum class SkillID {
  None, NormalAttack, Heal, 
  Slime_Attack, 
  Goblin_Stab, Goblin_SneakAttack, Goblin_Bash
};

struct SkillDetail {
  SkillEffect effect;
  int value;
};

struct SkillInfo{
  std::string skill_name;       //技能名稱
  std::string skill_info;       //技能簡述
  SkillEffect main_use;         //技能的主要用途(敵人出招判斷用，玩家不影響)
  int cd;                       //技能冷卻
  std::vector<SkillDetail> skill_detail;   //  技能效果
};

class SkillDataBase {
public:
  static SkillInfo GetSkillInfo(SkillID skill_id, int atk);
};




#endif