#include "../include/Enemy.h"


int Enemy::GetExpReward() const {
  return exp_reward;
}

int Enemy::GetCoinReward() const {
  return coin_reward;
}

int Enemy::GetNumOfSkill() const {
  return num_of_skill;
}

void Enemy::SetExpReward(int exp_reward) {
  this->exp_reward = exp_reward;
}

void Enemy::SetCoinReward(int coin_reward) {
  this->coin_reward = coin_reward;
}

void Enemy::SetNumOfSkill(int num) {
  this->num_of_skill = num;
}

Slime::Slime() {
  SetName("史萊姆");
  SetHp(30);
  SetMaxHp(30);
  SetATK(6);
  SetSpeed(6);
  SetElement(Grass);
  SetExpReward(10);
  SetCoinReward(5);
  SetNumOfSkill(1);
}

void Enemy::PrintInfo() const {
  // 之後再做 IO::PrintEnemyInfo
}