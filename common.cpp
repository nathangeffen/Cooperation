#include "common.h"

std::mt19937 mersenne_twister;
std::uniform_real_distribution<> random_engine_double(0,1);
std::uniform_int_distribution<> random_engine_int;

double drand() { return random_engine_double( mersenne_twister ); };

int irand( int upper ) {
  int rand = random_engine_int( mersenne_twister );
  return rand % upper;
};

