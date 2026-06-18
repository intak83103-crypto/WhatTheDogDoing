#include "../include/User.h"

#include <cstddef>

#include "../include/IO.h"
#include "../include/Random.h"

User::User() {}

User::User(std::string name, int id) {
  this->name = name;
  this->id = id;
  id_of_dd = 1;
  IO::PrintUserSetUp(name,id);
  std::string dd_name;
  IO::FirstDD();
  dogdoings.emplace_back(DogDoing(id_of_dd++));
  curr_dd = 0;
  coin = 50;
  LearnSkill(SkillID::NormalAttack);
  backpack = {};
}

int User::GetNumOfDD() const {
  return dogdoings.size();
}

DogDoing& User::GetCurrentDD() {
  return dogdoings[curr_dd];
}

int User::GetCurrDDIndex() const {
  return curr_dd;
}

std::string User::GetUserName() const {
  return name;
}

void User::SetName() {
  std::string str;
  IO::PrintSetUserName(name);
  IO::GetToken(str);
  name = str;
  PrintInfo();
}

DogDoing& User::GetDD(int index) {
  return dogdoings[index];
}

void User::AddDD() {
  dogdoings.emplace_back(DogDoing(id_of_dd++));
  curr_dd = dogdoings.size() - 1;
}

int User::GetCoin() const {
  return coin;
}

void User::AddCoin(int coins) {
  coin += coins;
}

bool User::PayCoin(int price) {
  if ( price > coin ) {
    IO::PrintNotEnoughCoin();
    return false;
  }
  coin -= price;
  return true;
}

bool User::HasSkill(SkillID skill) const {
  for ( SkillID owned_skill : skill_list ) {
    if ( owned_skill == skill ) {
      return true;
    }
  }
  return false;
}

bool User::LearnSkill(SkillID skill) {
  if ( skill == SkillID::None ) {
    return false;
  }
  if ( HasSkill(skill) ) {
    return false;
  }
  skill_list.push_back(skill);
  return true;
}

SkillID User::LearnRandomSkillFromJar() {
  for ( int i = 0; i < 20; i++ ) {
    SkillID skill = SkillDataBase::GetRandomJarSkill();
    if ( LearnSkill(skill) ) {
      IO::PrintLearnSkill(skill, "技能罐");
      return skill;
    }
  }
  IO::PrintSkillLibraryFull();
  return SkillID::None;
}

SkillID User::TryDropSkill(const std::vector<SkillID>& enemy_skills) {
  if ( Random::RandomChance(35) == false ) {
    IO::PrintNoSkillDrop();
    return SkillID::None;
  }

  std::vector<SkillID> drop_pool;
  for ( SkillID skill : enemy_skills ) {
    if ( skill == SkillID::None || skill == SkillID::NormalAttack ) {
      continue;
    }
    if ( HasSkill(skill) == false ) {
      drop_pool.push_back(skill);
    }
  }

  if ( drop_pool.empty() ) {
    IO::PrintSkillLibraryFull();
    return SkillID::None;
  }

  int drop_index = Random::RandomInt(0, drop_pool.size() - 1);
  SkillID skill = drop_pool[drop_index];
  LearnSkill(skill);
  IO::PrintLearnSkill(skill, "怪物掉落");
  return skill;
}

bool User::IsSkillEquipped(SkillID skill, int except_dd) const {
  if ( skill == SkillID::NormalAttack ) {
    return false;
  }

  int n = dogdoings.size();
  for ( int i = 0; i < n; i++ ) {
    if ( i == except_dd ) {
      continue;
    }
    if ( dogdoings[i].HasSkill(skill) ) {
      return true;
    }
  }
  return false;
}

bool User::EquipSkillToCurrentDD(int slot, int skill_index) {
  int real_skill_index = skill_index - 1;
  if ( real_skill_index < 0 ||
       static_cast<std::size_t>(real_skill_index) >= skill_list.size() ) {
    IO::PrintSkillSelectError();
    return false;
  }

  SkillID skill = skill_list[real_skill_index];
  if ( slot == 1 && skill != SkillID::NormalAttack ) {
    IO::PrintNormalAttackError();
    return false;
  }
  if ( slot != 1 && skill == SkillID::NormalAttack ) {
    IO::PrintNormalAttackError();
    return false;
  }
  if ( IsSkillEquipped(skill, curr_dd) ) {
    IO::PrintSkillAlreadyEquipped();
    return false;
  }
  bool success = dogdoings[curr_dd].SetSkill(slot, skill);
  if ( success ) {
    IO::PrintEquipSkillSuccess(dogdoings[curr_dd].GetName(), slot, skill);
  }
  return success;
}

void User::ListSkillLibrary() const {
  IO::ListSkillLibrary(name, skill_list);
}

void User::GrantAllSkills() {
  std::vector<SkillID> all_skills = SkillDataBase::GetAllLearnableSkills();
  for ( SkillID skill : all_skills ) {
    LearnSkill(skill);
  }
}

void User::GrantAllElementDogDoings() {
  dogdoings.emplace_back(DogDoing("FireDogDoing", Element::Fire));
  dogdoings.emplace_back(DogDoing("WaterDogDoing", Element::Water));
  dogdoings.emplace_back(DogDoing("ThunderDogDoing", Element::Thunder));
  dogdoings.emplace_back(DogDoing("GrassDogDoing", Element::Grass));
  dogdoings.emplace_back(DogDoing("DarkDogDoing", Element::Dark));
  dogdoings.emplace_back(DogDoing("LightDogDoing", Element::Light));
  curr_dd = dogdoings.size() - 1;
}

void User::PrintInfo() const {
  IO::PrintUserInfo({name, GetNumOfDD(), coin});
}

void User::SwitchDD(int index) {
  if ( index <= 0 || static_cast<std::size_t>(index) > dogdoings.size() ) {
    IO::PrintSwitchDDError();
    return;
  }
  curr_dd = index - 1;
  IO::PrintSwitchDDSuccess(dogdoings[curr_dd].GetName());
}

void User::GetItem(ItemType type) {
  int n = backpack.size();
  for ( int i = 0; i < n; i ++ ) {
    if ( backpack[i].type == type ) {
      backpack[i].count += 1;
      return;
    }
  }
  backpack.push_back({type, 1});
}

void User::ListBackpack(bool divider) {
  std::vector<BackpackInfo> item;
  int n = backpack.size();
  for ( int i = 0; i < n; i++ ) {
    ItemInfo info = ItemDatabase::GetInfo(backpack[i].type);
    item.push_back({info.name, backpack[i].count});
  }
  IO::ListBackpack(name, item, divider);
}

void User::UseItem(int index, int target_dd) {
  int real_index = index - 1;
  if ( real_index < 0 ||
       static_cast<std::size_t>(real_index) >= backpack.size()  ) {
    IO::UseItemError();
    return;
  }
  if ( backpack[real_index].count <= 0 ) {
    DeleteItem(real_index);
    return;
  }
  if ( target_dd != -1 && DogDoingIndexCheck(target_dd - 1) == false ) {
    return;
  }
  ItemDatabase::UseItem(*this, backpack[real_index].type, target_dd);

  backpack[real_index].count -= 1;

  if ( backpack[real_index].count <= 0 ) {
    DeleteItem(real_index);
  }
}
void User::DeleteItem(int index) {
  backpack.erase(backpack.begin() + index);
}
ItemType User::GetItemOfBackpack(int index) {
  index--;
  if ( BackpackIndexCheck(index) ) {
    return backpack[index].type;
  }
  return ItemType::None;
}

void User::ListAllDD() const {
  IO::ListAllDD(GetAllDDtitleInfo(), name, curr_dd);
}

std::vector<DDtitleInfo> User::GetAllDDtitleInfo() const {
  std::vector<DDtitleInfo> ddstitle;
  for ( DogDoing dd : dogdoings ) {
    ddstitle.push_back(dd.TitlePackage());
  }
  return ddstitle;
}

DogDoing* User::GetIndexOfDD(int index) {
  int real_index = index - 1;
  if ( DogDoingIndexCheck(real_index) ) {
    return &dogdoings[real_index];
  }
  return nullptr;
}
bool User::BackpackIndexCheck(int index) const {
  int n = backpack.size();
  if ( index < 0 || index >= n ) {
    return false;
  }
  return true;
}

bool User::DogDoingIndexCheck(int index) const {
  int n = dogdoings.size();
  if ( index < 0 || index >= n ) {
    IO::PrintSwitchDDError();
    return false;
  }
  return true;
}
