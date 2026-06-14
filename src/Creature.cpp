#include "../include/Creature.h"
#include "../include/IO.h"

Creature::Creature(CreatureInfo info) {
  name = info.name;
  hp = info.hp;
  max_hp = info.max_hp;
  attack = info.attack;
  speed = info.speed;
  element = info.element;
  ult_energy = info.ult_energy;
  max_ult_energy = info.max_ult_energy;
  num_of_skill = info.num_of_skill;
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

int Creature::GetSpeed() const {
  return speed;
}

int Creature::GetMaxHp() const {
  return max_hp;
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
    attack,
    speed,
    name,
    element,
    ult_energy,
    max_ult_energy,
    num_of_skill
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


int Creature::GetUltEnergy() const {
  return ult_energy;
}

int Creature::GetMaxUltEnergy() const {
  return max_ult_energy;
}

void Creature::SetElement(Element element) {
  this->element = element;
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

bool Creature::AddSkill(SkillID skill) {
  if ( num_of_skill >= 4 ) {

    return false;
  }
  skill_list[num_of_skill++] = skill;
  return true;
}

bool Creature::DeleteSKill(int index) {
  index--;
  if ( index == 0 ) {
    IO::PrintNormalAttackError();
    return false;
  }
  if ( index <= 0 || index >= 4 || skill_list[index] == SkillID::None) {
    IO::PrintSkillSelectError();
    return false;
  }
  skill_list[index] = SkillID::None;
  num_of_skill--;
  return true;
}

SkillID Creature::GetIndexOfSkillList(int index) const {
  index--;
  if ( index < 0 || index > 3 ) {
    return SkillID::None;
  }
  return skill_list[index];
}

void Creature::MinusHp(int minus) {
  hp -= minus;
  if ( hp <= 0 ) {
    hp = 0;
  }
  
}

int Creature::GetNumOfSkill() const {
  return num_of_skill;
}

void Creature::SetNumOfSkill(int num) {
  num_of_skill = num;
}

int Creature::GetSkillCD(int index) const {
  index--;
  if ( index < 0 || index >= 4 ) {
    return -1;
  }
  return skill_cd[index];
}

bool Creature::CanUseSkill(int index) const {
  if ( GetSkillCD(index) > 0 ) {
    return false;
  }
  return true;
}

void Creature::SetSkillCd(int index, int cd) {
  skill_cd[--index] = cd;
}

void Creature::ReduceSkillCD() {
  for ( int i = 0; i < num_of_skill; i++ ) {
    skill_cd[i]--;
    if ( skill_cd[i] <= 0 ) {
      skill_cd[i] = 0;
    }
  }
}
void Creature::ReSetSkillCD(int index) {
  index--;
  SkillID id = skill_list[index];
  SkillInfo info = SkillDataBase::GetSkillInfo(id, attack);
  skill_cd[index] = info.cd;
}

void Creature::ResetSkillCD() {
  for ( int i = 0; i < 4; i++ ) {
    skill_cd[i] = 0;
  }
}
