#include "../include/Creature.h"

Creature::Creature(CreatureInfo info) {
  name = info.name;
  hp = info.hp;
  max_hp = info.hp;
  mp = info.max_mp;
  max_mp = info.max_mp;
  attack = info.attack;
  speed = info.speed;
}

Creature::Creature() {

}

std::string Creature::GetName() const {
  return name;
}

double Creature::GetATK() const {
  return attack;
}

double Creature::GetHp() const {
  return hp;
}

double Creature::GetMp() const {
  return mp;
}

int Creature::GetSpeed() const {
  return speed;
}

double Creature::GetMaxHp() const {
  return max_hp;
}

double Creature::GetMaxMp() const {
  return max_mp;
}

void Creature::SetName(std::string name) {
  this->name = name;
}

void Creature::Heal(int heal) {
  hp += heal;
  if ( hp >= max_hp ) {
    hp = max_hp;
  }
}

CreatureInfo Creature::GetCreatureInfo() const{
  return {hp, max_hp, mp, max_mp, attack, speed, name};
}

void Creature::SetATK(double atk) {
  this->attack = atk;
}

void Creature::SetHp(double hp) {
  this->hp = hp;
}

void Creature::SetMaxHp(double max_hp) {
  this->max_hp = max_hp;
}

void Creature::SetMaxMp(double max_mp) {
  this->max_mp = max_mp;
}

void Creature::SetMp(double mp) {
  this->mp = mp;
}

void Creature::SetSpeed(int speed) {
  this->speed = speed;
}
