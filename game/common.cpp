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

#include "common.h"
#include "game.h"

using namespace std;

mt19937 mersenne_twister;
uniform_real_distribution<> random_engine_double(0,1);
uniform_int_distribution<> random_engine_int;

double drand() { return random_engine_double( mersenne_twister ); }

int irand( int upper ) {
  int rand = random_engine_int( mersenne_twister );
  return rand % upper;
}

void setupCommandLine( po::options_description& options,
                       int& iterations, int& rand_seed )
{
  options.add_options()
      ("help", "produce help message")
      ("iterations",  po::value<int>(&iterations)->default_value(1000),
                                "iterations to execute")
      ("verbose", "output as much as possible")
      ("shuffle", "randomly shuffle the players before starting the game")
      ("print-contests-csv", "output results of individual contests in csv format")
      ("print-results-csv", "output final results and statistics in csv format")
      ("randseed", po::value<int>(&rand_seed), "set the random seed");
  for ( auto c : registeredCompetitors ) {
    QString description = "include arg copies of " + c.first + " in competition";
    options.add_options()(c.first.toStdString().c_str(), po::value<int>(),
                       description.toLower().toStdString().c_str() );
  }

}

int processCommandLine( const po::options_description& options,
                        const po::variables_map& vm,
                        int iterations, int rand_seed )
{
  Game game;

  try {
    if (vm.count("help")) {
      cout << options << "\n";
      return 1;
    }

    game.setIterations(iterations);

    for ( auto entry : registeredCompetitors ) {
      if (vm.count( entry.first.toLower().toStdString() )) {
        for (int i=0; i<vm[entry.first.toLower().toStdString()].as<int>(); i++) {
          game.addCompetitor(entry.second);
        }
      }
    }
    if ( vm.count("randseed") ) {
      game.setRandomSeed( rand_seed );
    }

    if ( vm.count("shuffle") ) {
      game.shuffleCompetitors();
    }

    bool print_contests_csv = false;
    if ( vm.count("print-contests-csv") || vm.count("verbose") ) {
      print_contests_csv = true;
    }
    game.play(print_contests_csv);


    if ( vm.count("print-results-csv") || vm.count("verbose") ) {
      game.output();
    }
  }
  catch(exception& e) {
      cerr << "error: " << e.what() << "\n";
      return 1;
  }
  return 0;
}

