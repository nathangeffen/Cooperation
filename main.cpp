#include <boost/program_options.hpp>

#include "competitor.h"
#include "common.h"
#include "game.h"
#include "gui.h"

using namespace std;

namespace po = boost::program_options;

int main(int argc, char *argv[])
{

  Game game;
  int iterations;
  int rand_seed;

  try {

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("iterations",  po::value<int>(&iterations)->default_value(1000),
                                  "iterations to execute")
        ("verbose", "output as much as possible")
        ("shuffle", "randomly shuffle the players before starting the game")
        ("print-contests-csv", "output results of individual contests in csv format")
        ("print-results-csv", "output final results and statistics in csv format")
        ("randseed", po::value<int>(&rand_seed), "set the random seed")
        ("gui",
         "run graphical user interface and specify display methodology of 'ratio' or 'rank'");

    for ( auto c : registeredCompetitors ) {
      QString description = "include n copies of " + c.first + " in competition";
      desc.add_options()(c.first.toStdString().c_str(), po::value<int>(),
                         description.toLower().toStdString().c_str() );
    }
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      cout << desc << "\n";
      return 1;
    }

    if ( vm.count("gui") ) {
      Gui(game).start();
      return 0;
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
