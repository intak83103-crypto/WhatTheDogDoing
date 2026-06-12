#include "../include/Random.h"



int Random::RandomInt(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(min, max);
  return dist(gen);
}

bool Random::RandomChance(int percent) {
  return RandomInt(1, 100) <= percent;
}