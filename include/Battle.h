#ifndef BATTLE_H
#define BATTLE_H

class User;
class DogDoing;
class Creature;

#include "DisplayData.h"

class Battle{
private:
  User& user;
  DogDoing& dogdoing;
  Creature& enemy;
  int turn = 1;
  int dd_over_hit = 0;
  int enemy_over_hit = 0;
  
public:
  Battle(User& user, DogDoing& dogdoing, Creature& enemy); 
  int CalculateDamage(bool is_enemy = false);
  bool IsHit(bool is_enemy = false);
  bool IsCrit(bool is_enemy = false);
  void Run();
  void SetOverHit(bool is_enemy, int over_hit);

};




#endif 
