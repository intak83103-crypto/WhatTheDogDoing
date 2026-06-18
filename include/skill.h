#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <vector>

enum class SkillEffect {    // 技能效果
  None, Attack, Heal, Defend, Buff, BonusTurn
};

enum class SkillID {        //   角色存取的都是ID，用的時候才會用ID查功能
  None, NormalAttack, Heal, 
  QuickSlash, PowerStrike, Regeneration, GuardBreak, FlameBurst,
  IronSkin, Focus, Haste, PoisonNeedle, LifeBloom, LastStand,
  ThunderStrike, VitalStrike,
  Slime_Attack, 
  Goblin_warCry, Goblin_SneakAttack, Goblin_Bash,
  Vampire_Normal, Vampire_Drain, Vampire_BloodLust, Vampire_Blood_Mist,
  DemonHunter_ExecutionStance, DemonHunter_DemonPiercingBolt, DemonHunter_HolyPurge
};

enum class SkillRarity {
  Common,
  Rare,
  Epic
};

enum class SkillControl{    // 技能分成需要命中或是直接生效（為了吸血攻擊設計）
 None, Always, AttackHit, AttackCrit
};

enum class BattleBuffType{
  NoBuff, AddAttack, AddHp, AddMaxHp, AddDamageIncrease, AddHitRate, AddDodgeRate, AddCritRate, AddSpeed,
  AddDefend, AddMaxHpPercent, DotDamage, HotHeal, ExtraTurnOnCrit
};

enum class BuffTarget {
  Self,
  Opponent
};

enum class BuffValueType {
  Fixed,
  Percent
};

enum class SkillValueType {     //不只有用攻擊力出傷得角色
  Fixed,
  AtkPercent,
  MaxHpPercent,
  CurrentHpPercent,
  LostHpPercent,
  Damage
};

struct BuffInfo {                 // buff詳情
  BattleBuffType buff_type;  
  BuffTarget target;
  BuffValueType value_type;
  std::string buff_name;     
  int round;                       //持續時間
  int value;
};

struct SkillDetail {
  SkillEffect effect;
  int value;
  SkillControl control;
  SkillValueType value_type = SkillValueType::Fixed;
};

struct SkillInfo{
  std::string skill_name;       //技能名稱
  std::string skill_info;       //技能簡述
  SkillEffect main_use;         //技能的主要用途(敵人出招判斷用，玩家不影響)
  int cd;                       //技能冷卻
  std::vector<SkillDetail> skill_detail;   //  技能效果
  std::vector<BuffInfo> buff_info;
};

struct SkillResultDetail {
  SkillEffect effect;
  int value;
  bool success;
  bool is_crit = false;
  std::string detail_text = "";
};

struct SkillResult {
  std::string skill_name;
  std::vector<SkillResultDetail> details;
};

class SkillDataBase {
public:
  static SkillInfo GetSkillInfo(SkillID skill_id);
  static SkillRarity GetSkillRarity(SkillID skill_id);
  static std::string GetSkillRarityName(SkillID skill_id);
  static std::vector<SkillID> GetAllLearnableSkills();
  static SkillID GetRandomJarSkill();
  static SkillID GetRandomDropSkill(int enemy_level);
};




#endif
