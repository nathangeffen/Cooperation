/* This source file is part of Cooperation, an implementation of the 
 * Prisoner's Dilemna game.
 *
 * Copyright (C) 2012 by Nathan Geffen 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_H
#define COMMON_H

#include <random>

#include <boost/program_options.hpp>

/** Common functions and global variables.
  */

namespace po = boost::program_options;

const double PI = 3.14159265;
class options_description; // Used to process command line arguments

/** Global instances of random generators
  */
extern std::mt19937 mersenne_twister;
extern std::uniform_real_distribution<> random_engine_double;
extern std::uniform_int_distribution<> random_engine_int;
extern double drand();
extern int irand(int);

/** Sets up acceptable command line options.
  */
void setupCommandLine( po::options_description& options,
                       int& iterations,
                       int& rand_seed );

/** Processes the command line options.
  */
int processCommandLine( const po::options_description& options,
                        const po::variables_map& vm,
                        int iterations, int rand_seed );

#endif // COMMON_H
