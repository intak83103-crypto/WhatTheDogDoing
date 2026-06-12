#include "../include/Creature.h"

Creature::Creature(CreatureInfo info) {
  name = info.name;
  hp = info.hp;
  max_hp = info.max_hp;
  mp = info.mp;
  max_mp = info.max_mp;
  attack = info.attack;
  speed = info.speed;
  element = info.element;
  ult_type = info.ult_type;
  ult_energy = info.ult_energy;
  max_ult_energy = info.max_ult_energy;
}

Creature::Creature() {

}

std::string Creature::GetName() const {
  return name;
}

int Creature::GetATK() const {
  return attack;
}

int Creature::GetHp() const {
  return hp;
}

int Creature::GetMp() const {
  return mp;
}

int Creature::GetSpeed() const {
  return speed;
}

int Creature::GetMaxHp() const {
  return max_hp;
}

int Creature::GetMaxMp() const {
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
  return {
    hp,
    max_hp,
    mp,
    max_mp,
    attack,
    speed,
    name,
    element,
    ult_type,
    ult_energy,
    max_ult_energy
  };
}

void Creature::SetATK(int atk) {
  this->attack = atk;
}

void Creature::SetHp(int hp) {
  this->hp = hp;
}

void Creature::SetMaxHp(int max_hp) {
  this->max_hp = max_hp;
}

void Creature::SetMaxMp(int max_mp) {
  this->max_mp = max_mp;
}

void Creature::SetMp(int mp) {
  this->mp = mp;
}

void Creature::SetSpeed(int speed) {
  this->speed = speed;
}

int Creature::GetHitRate() const {
  return hit_rate;
}

int Creature::GetCritRate() const {
  return  crit_rate;
}

int Creature::GetDodgeRate() const {
  return dodge_rate;
}

int Creature::GetDamageIncrease() const {
  return damage_increase;
}

Element Creature::GetElement() const {
  return element;
}

UltType Creature::GetUltType() const {
  return ult_type;
}

int Creature::GetUltEnergy() const {
  return ult_energy;
}

int Creature::GetMaxUltEnergy() const {
  return max_ult_energy;
}

bool Creature::CanUseUlt() const {
  return ult_type != NoUlt && ult_energy >= max_ult_energy;
}

void Creature::SetElement(Element element) {
  this->element = element;
}

void Creature::SetUltType(UltType ult_type) {
  this->ult_type = ult_type;
}

void Creature::SetMaxUltEnergy(int max_ult_energy) {
  this->max_ult_energy = max_ult_energy;
  if ( ult_energy > max_ult_energy ) {
    ult_energy = max_ult_energy;
  }
}

void Creature::AddUltEnergy(int value) {
  ult_energy += value;
  if ( ult_energy > max_ult_energy ) {
    ult_energy = max_ult_energy;
  }
  if ( ult_energy < 0 ) {
    ult_energy = 0;
  }
}

void Creature::UseUltEnergy() {
  ult_energy = 0;
}
