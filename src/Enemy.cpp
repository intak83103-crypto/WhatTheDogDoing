#include "../include/Enemy.h"
#include "../include/IO.h"

int Enemy::GetExpReward() const {
  return exp_reward;
}

int Enemy::GetCoinReward() const {
  return coin_reward;
}

int Enemy::GetLevel() const {
  return level;
}



void Enemy::SetExpReward(int exp_reward) {
  this->exp_reward = exp_reward;
}

void Enemy::SetCoinReward(int coin_reward) {
  this->coin_reward = coin_reward;
}

void Enemy::SetLevel(int level) {
  this->level = level;
}

void Enemy::PrintBattleInfo() const {
  IO::PrintBattleInfo(GetCreatureInfo());
  ListSkill();
}

Slime::Slime() {
  SetName("史萊姆");
  SetLevel(1);
  SetHp(40);
  SetMaxHp(40);
  SetATK(6);
  SetSpeed(3);
  SetExpReward(12);
  SetCoinReward(5);
  AddSkill(SkillID::NormalAttack);
  AddSkill(SkillID::Heal);
  AddSkill(SkillID::Slime_Attack);
}

void Enemy::PrintInfo() const {
  // 之後再做 IO::PrintEnemyInfo
}

FireSlime::FireSlime() : Slime(){
  SetElement(Element::Fire);
  SetName("火史萊姆");
}

WaterSlime::WaterSlime() : Slime(){
  SetElement(Element::Water);
  SetName("水史萊姆");
}

GrassSlime::GrassSlime() : Slime(){
  SetElement(Element::Grass);
  SetName("草史萊姆");
}

ThunderSlime::ThunderSlime() : Slime(){
  SetElement(Element::Thunder);
  SetName("雷史萊姆");
}

DarkSlime::DarkSlime() : Slime(){
  SetElement(Element::Dark);
  SetName("暗史萊姆");
}

LightSlime::LightSlime() : Slime(){
  SetElement(Element::Light);
  SetName("光史萊姆");
}

Goblin::Goblin() {
  SetName("哥布林");
  SetLevel(3);
  SetHp(72);
  SetMaxHp(72);
  SetATK(11);
  SetSpeed(8);
  SetExpReward(25);
  SetCoinReward(10);
  AddSkill(SkillID::NormalAttack);
  SetElement(Element::None);
  AddSkill(SkillID::Goblin_Bash);
  AddSkill(SkillID::Goblin_warCry);
  AddSkill(SkillID::Goblin_SneakAttack);
}

Vampire::Vampire() {
  SetName("吸血鬼");
  SetLevel(5);
  SetHp(80);
  SetMaxHp(80);
  SetSpeed(15);
  SetATK(5);
  SetExpReward(50);
  SetCoinReward(20);
  SetElement(Element::Dark);
  AddSkill(SkillID::Vampire_Normal);
  AddSkill(SkillID::Vampire_BloodLust);
  AddSkill(SkillID::Vampire_Drain);
  AddSkill(SkillID::Vampire_Blood_Mist);
}

DemonHunter::DemonHunter() {
  SetName("獵魔士");
  SetLevel(6);
  SetHp(95);
  SetMaxHp(95);
  SetSpeed(12);
  SetATK(12);
  SetExpReward(55);
  SetCoinReward(30);
  SetElement(Element::Light);
  AddSkill(SkillID::NormalAttack);
  AddSkill(SkillID::DemonHunter_HolyPurge);
  AddSkill(SkillID::DemonHunter_DemonPiercingBolt);
  AddSkill(SkillID::DemonHunter_ExecutionStance);
}

StoneGuardian::StoneGuardian() {
  SetName("石甲守衛");
  SetLevel(3);
  SetHp(92);
  SetMaxHp(92);
  SetATK(12);
  SetSpeed(9);
  SetExpReward(45);
  SetCoinReward(18);
  SetElement(Element::None);
  AddSkill(SkillID::NormalAttack);
  AddSkill(SkillID::GuardBreak);
  AddSkill(SkillID::Goblin_Bash);
  AddSkill(SkillID::Regeneration);
}

OrcWarrior::OrcWarrior() {
  SetName("獸人戰士");
  SetLevel(5);
  SetHp(132);
  SetMaxHp(132);
  SetATK(17);
  SetSpeed(12);
  SetExpReward(70);
  SetCoinReward(28);
  SetElement(Element::Fire);
  AddSkill(SkillID::NormalAttack);
  AddSkill(SkillID::Goblin_warCry);
  AddSkill(SkillID::PowerStrike);
  AddSkill(SkillID::GuardBreak);
}

VampireDuke::VampireDuke() {
  SetName("血族公爵");
  SetLevel(8);
  SetHp(170);
  SetMaxHp(170);
  SetATK(21);
  SetSpeed(18);
  SetExpReward(120);
  SetCoinReward(45);
  SetElement(Element::Dark);
  AddSkill(SkillID::Vampire_Normal);
  AddSkill(SkillID::Vampire_BloodLust);
  AddSkill(SkillID::Vampire_Drain);
  AddSkill(SkillID::FlameBurst);
}

AbyssKing::AbyssKing() {
  SetName("深淵王");
  SetLevel(10);
  SetHp(235);
  SetMaxHp(235);
  SetATK(29);
  SetSpeed(22);
  SetExpReward(180);
  SetCoinReward(80);
  SetElement(Element::Dark);
  AddSkill(SkillID::NormalAttack);
  AddSkill(SkillID::DemonHunter_ExecutionStance);
  AddSkill(SkillID::FlameBurst);
  AddSkill(SkillID::Vampire_Drain);
}
