#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random{
public:

  static int RandomInt(int min, int max);

  static bool RandomChance(int percent);
};


#endif