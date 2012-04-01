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
