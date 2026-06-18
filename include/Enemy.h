#ifndef ENEMY_H
#define ENEMY_H

#include "Creature.h"

class Enemy : public Creature {
private:
  int exp_reward = 0;
  int coin_reward = 0;
  int level = 1;

public:
  int GetExpReward() const;
  int GetCoinReward() const;
  int GetLevel() const;
  void SetExpReward(int exp_reward);
  void SetCoinReward(int coin_reward);
  void SetLevel(int level);
  void PrintInfo() const override;
  void PrintBattleInfo() const override;
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

class LightSlime : public Slime {
public:
  LightSlime();
};

class Goblin : public Enemy {
public:
  Goblin();
};

class Vampire : public Enemy {
public:
  Vampire();
};

class DemonHunter : public Enemy {
public:
  DemonHunter();
};

class StoneGuardian : public Enemy {
public:
  StoneGuardian();
};

class OrcWarrior : public Enemy {
public:
  OrcWarrior();
};

class VampireDuke : public Enemy {
public:
  VampireDuke();
};

class AbyssKing : public Enemy {
public:
  AbyssKing();
};

#endif
