#include <boost/program_options.hpp>

#include "competitor.h"
#include "game.h"

using namespace std;

namespace po = boost::program_options;

int main(int argc, char *argv[])
{

  Game game;
  int iterations;

  map < string, competitor_ptr > competitor_map;

  competitor_map[TITFORTAT] = competitor_ptr ( new TitForTatCompetitor );
  competitor_map[ALWAYSDEFECT] = competitor_ptr ( new AlwaysDefectCompetitor );
  competitor_map[RANDOM] = competitor_ptr ( new RandomCompetitor );
  competitor_map[ALWAYSCOOP] = competitor_ptr( new AlwaysCooperateCompetitor );
  competitor_map[OPPOSITE] = competitor_ptr( new OppositeCompetitor );
  competitor_map[TITFORTATRAND] = competitor_ptr( new TitForTatWithRandomCompetitor );

  try {

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("iterations",  po::value<int>(&iterations)->default_value(1000),
                                  "iterations to execute")
        ("print-contests-csv", "output results of individual contests in csv format")
        ("print-stats-csv", "output final statistics in csv format")
        ("randseed", "set the random seed")
        ("gui", "run graphical user interface");
      ;

    for ( auto c : competitor_map ) {
      string description = "include n copies of " + c.first + " in competition";
      desc.add_options()(c.first.c_str(), po::value<int>(),
                         description.c_str() );
    }
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      cout << desc << "\n";
      return 1;
    }
    game.setIterations(iterations);

    for ( auto entry : competitor_map ) {
      if (vm.count( entry.first)) {
        for (int i=0; i<vm[entry.first].as<int>(); i++) {
          game.addCompetitor(entry.second);
        }
      }
    }
  }
  catch(exception& e) {
      cerr << "error: " << e.what() << "\n";
      return 1;
  }
  catch(...) {
      cerr << "Exception of unknown type!\n";
  }

  game.play();
  game.output();

  return 0;
}
