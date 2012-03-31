#include <boost/program_options.hpp>

#include "game/common.h"
#include "game/game.h"
#include "gui.h"

namespace po = boost::program_options;

int main( int argc, char *argv[] )
{
  int iterations = 1000, rand_seed = 0;
  po::options_description options("Allowed options");
  setupCommandLine( options, iterations, rand_seed );
  options.add_options()
       ("gui",
        "run graphical user interface and specify display methodology of 'ratio' or 'rank'");

  po::variables_map vm;
  po::store(po::parse_command_line( argc, argv, options ), vm);
  po::notify(vm);

  if ( argc < 2 || vm.count( "gui") ) {
    Game game;
    Gui(game).start();
    return 0;
  } else {
    return processCommandLine( options, vm, iterations, rand_seed );
  }
}
