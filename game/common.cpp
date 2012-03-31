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

