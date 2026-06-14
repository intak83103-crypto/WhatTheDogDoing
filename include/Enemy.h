#ifndef ENEMY_H
#define ENEMY_H

#include "Creature.h"

class Enemy : public Creature {
private:
  int exp_reward = 0;
  int coin_reward = 0;

public:
  int GetExpReward() const;
  int GetCoinReward() const;
  void SetExpReward(int exp_reward);
  void SetCoinReward(int coin_reward);
  void PrintInfo() const override;
};


class Slime : public Enemy {
public:
  Slime();
};

class FireSlime : public Slime {
public:
  FireSlime();
};

class WaterSlime : public Slime {
public:
  WaterSlime();
};

class GrassSlime : public Slime {
public:
  GrassSlime();
};

class ThunderSlime : public Slime {
public:
  ThunderSlime();
};

class DarkSlime : public Slime {
public:
  DarkSlime();
};




#endif
