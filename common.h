#ifndef COMMON_H
#define COMMON_H

#include <random>

const double PI = 3.14159265;

extern std::mt19937 mersenne_twister;
extern std::uniform_real_distribution<> random_engine_double;
extern std::uniform_int_distribution<> random_engine_int;
extern double drand();
extern int irand(int);
class ostream;
class QString;
std::ostream& operator<<( const std::ostream& os, const QString& s);

enum DisplayMethodology {
  RATIO = 0,
  RATIO_WITH_MIN_AT_0,
  RANK
};

#endif // COMMON_H
