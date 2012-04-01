# Cooperation

## An implementation of the Prisoner's Dilemna game

### Introduction

*Cooperation* is an implementation of the Prisoner's Dilemna game. In one of the most popular versions of the Prisoner's Dilemna, players are matched against each other and have to make one of two choices: DEFECT or COOPERATE. 

Players are awarded points as follows:

- If both players defect, both get zero points.
- If both players co-operate, they get one point each.
- If one player defects and the other co-operates, the defector gets two points.

Each competitor aims to maximise its points.

This implementation also has these characteristics:

- The only knowledge a competitor has about its opponent is the decisions taken by both itself and its opponent in their previous matches.
- The user specifies the number of iterations the game will be played.
- On each iteration the players are randomly matched against each other.- 
- The game can be played with a graphical user interface or from the command line.
- Results of all matches and the statistics of each game are output in CSV format. This data is written to standard output if the command line version is used and to a file called prisonerslog.csv by the GUI. The file is overwritten each time a game is executed.

Cooperation is under development still. It is not production ready software. It comes with absolutely no guarantees.

Cooperation is licensed under GPL version 3.

### How to install it

Download the latest version of Cooperation from [github](https://github.com/nathangeffen/Cooperation "Cooperation on github") and unzip it into a folder of your choice.

Cooperation is currently developed on an Intel i3 running Linux Mint 12. It should be easy to compile it on any GNU/Linux system and it should be possible to compile it under Windows or OS/X, but I have not tested it. You need at least version 4.6 of the g++ compiler because it makes extensive use of C++ 11 features. You also need Qt 4. You might need qmake, but in theory you should be able to compile it just with *make*.

To create the executable, simply run *make*. The executable is called *cooperation*. 

### Graphical User Interface

Run *cooperation* or *cooperation --gui* to invoke Cooperation with a Graphical User Interface (GUI). The GUI is useful to learn how to use the program and to visualise the results. The first thing to do is to click the *Define New Game* icon or type *CTRL-n*. 

### Command line

Run *cooperation --help* to get a list of command line options. Here is an example:

    ./cooperation --iteration 10000 --verbose --shuffle --titfortat 10 --alwaysdefect 5 --pavlov 5 --randseed 146

The above example's options tell the program to run the game for 10,000 iterations, print all output, randomly shuffle the competitors upfront (probably really necessary), create 10 TITFORTAT, 5 ALWAYSDEFECT and 5 PAVLOV competitors, and set the random seed to 146.

### Competitors

This version comes with seven competitors implemented:

ALWAYSCOOPERATE
  ~ Always cooperates (a very poor competitor)

ALWAYSDEFECT
  ~ Always defects

OPPOSITE
  ~ Does the opposite of what its opponent did the last time they played. Randomly chooses on first encounter.

PAVLOV
  ~ If it and its opponent's decisions did not match on the previous encounter, defects, else co-operates. Co-operates on first encounter.
  
RANDOM
  ~ Randomly chooses.
 
TITFORTAT
  ~ Co-operates on first encounter. From then on repeats whatever the opponent did in their previous encounter. 
 
TITFORTATRANDOM
  ~ Same as TITFORTAT, except that 10% of the time, it defects where TITFORTAT would co-operate and co-operates where TITFORTAT would defect. Like TITFORTAT, it always co-operates on first encounter.
  
### How to implement your own Competitor
  
It is easy to implement your own competitor. You need to include "competitor.h" located in the game folder. Then call the macro REGISTER_COMPETITOR( Name_of_Your_Competitor ).

The macro sets up a calls named *Name_of_Your_Competitor* and implements all functionality except the virtual decision function. This you have to implement. For example, here is the implementation of ALWAYSCOOPERATE.

    #include "competitor.h"
    
    REGISTER_COMPETITOR( AlwaysCooperate );
   
    Choice AlwaysCooperate::decision(int) const {
      return COOPERATE;
    };
    
Here is the more sophisticated TITFORTAT implementation:

    Choice TitForTat::decision(int index) const
    {
      auto entry = history_.find( index );
      if ( entry  != history_.end() ) {
        return ( entry.value().back().second == COOPERATE ) ? COOPERATE: DEFECT;
      }
      return COOPERATE;
    }


*Choice* is an enumeration that can either be *COOPERATE* or *DEFECT*.

The *index* parameter uniquely identifies the opponent in the *history_* map.
The *history_* map is protected. It is defined as follows

    QMap <int, QVector <QPair <Choice, Choice> > > history_;

The first *Choice* in the QPair is this competitor's choice on the last encounter. The second *Choice* is the opponent's one.

### Improvements

- Make the scoring system user-definable.

- The code mixes Qt and STL containers. For consistency, in future this must be changed so that either only Qt containers are used or the non-GUI code exclusively uses STL. At present I would prefer the former option, but I'm open to being convinced otherwise.

- Implement threads for the game execution code that runs in parallel on multiple cores.

- The REGISTER_COMPETITOR macro needs to be improved.

- The implementation details of the Competitor class are too exposed. For example the history_ map should be private and exposed through access methods. 

- The GUI works but it needs lots of polishing.

- The non-Gui code should be packaged as a library.

### Acknowledgements

Qt, qmake and g++ made implementing this project possible and fun.

The icons in the GUI are from Emacs 23.

### Further reading and references

I first read about the Prisoner's Dilemna in Douglas Hofstadter's Metamagical Themas. It's a collection of Hofstadter's beautiful articles in Scientific American.

Axelrod, Robert. 1984. The Evolution of Cooperation. New York: Basic Books. (As references in Felkins L)

Felkins, Leon. 1995. The Prisoner's Dilemma. [http://perspicuity.net/sd/pd-brf.html](http://perspicuity.net/sd/pd-brf.html "Felkins webpage")

Hofstadter, Douglas R. 1983, "Metamagical Themas: Computer Tournaments of the Prisoner's Dilemma Suggest How Cooperation Evolves". Scientific American 248 (no.5):16-26. (As referenced in Felkins, 1995)

Wikipedia. Last accessed 2012-04-01. http://en.wikipedia.org/wiki/Prisoner's_dilemma

### Copyright

 Copyright (C) 2012 by Nathan Geffen 

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

