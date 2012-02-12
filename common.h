#ifndef COMMON_H
#define COMMON_H

#include <random>
#include <QString>

extern std::mt19937 mersenne_twister;
extern std::uniform_real_distribution<> random_engine_double;
extern std::uniform_int_distribution<> random_engine_int;
extern double drand();
extern int irand();
class ostream;
std::ostream& operator<<( const std::ostream& os, const QString& s);

#endif // COMMON_H