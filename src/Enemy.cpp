#include "../include/Enemy.h"
#include "../include/IO.h"

int Enemy::GetExpReward() const {
  return exp_reward;
}

int Enemy::GetCoinReward() const {
  return coin_reward;
}



void Enemy::SetExpReward(int exp_reward) {
  this->exp_reward = exp_reward;
}

void Enemy::SetCoinReward(int coin_reward) {
  this->coin_reward = coin_reward;
}

void Enemy::PrintBattleInfo() const {
  IO::EnemyPrintBattleInfo(GetCreatureInfo());
  ListSkill();
}

Slime::Slime() {
  SetName("史萊姆");
  SetHp(40);
  SetMaxHp(40);
  SetATK(6);
  SetSpeed(3);
  SetExpReward(12);
  SetCoinReward(5);
  SetNumOfSkill(1);
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

Goblin::Goblin() {
  SetName("哥布林");
  SetHp(72);
  SetMaxHp(72);
  SetATK(11);
  SetSpeed(8);
  SetExpReward(25);
  SetCoinReward(10);
  SetNumOfSkill(1);
  SetElement(Element::None);
  AddSkill(SkillID::Goblin_Bash);
  AddSkill(SkillID::Goblin_Stab);
  AddSkill(SkillID::Goblin_SneakAttack);
}

Vampire::Vampire() {
  SetName("吸血鬼");
  SetHp(100);
  SetMaxHp(100);
  SetSpeed(15);
  SetATK(16);
  SetExpReward(50);
  SetCoinReward(20);
  SetNumOfSkill(1);
  SetElement(Element::Dark);
  AddSkill(SkillID::Vampire_Claw);
  AddSkill(SkillID::Vampire_Drain);
}
