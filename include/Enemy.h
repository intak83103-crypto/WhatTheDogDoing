#ifndef ENEMY_H
#define ENEMY_H

#include "Creature.h"

class Enemy : public Creature {
private:
  int exp_reward = 0;
  int coin_reward = 0;
  int num_of_skill = 0;

public:
  int GetExpReward() const;
  int GetCoinReward() const;
  int GetNumOfSkill() const;
  void SetNumOfSkill(int num);
  void SetExpReward(int exp_reward);
  void SetCoinReward(int coin_reward);
  void PrintInfo() const override;
};


class Slime : public Enemy {
public:
  Slime();
};



#endif