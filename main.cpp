#include "competitor.h"
#include "game.h"

using namespace std;


int main(int argc, char *argv[])
{
  Game game(1000, 20);

  TitForTatCompetitor titForTat;
  AlwaysDefectCompetitor alwaysDefect;
  RandomCompetitor rdm;
  AlwaysCooperateCompetitor alwaysCooperate;
  OppositeCompetitor oppositeCompetitor;
  TitForTatWithRandom titForTatWithRandom;

  game.registerCompetitorType(&titForTat);
  game.registerCompetitorType(&alwaysDefect);
  //game.registerCompetitorType(&rdm);
  //game.registerCompetitorType(&alwaysCooperate);
  //game.registerCompetitorType(&oppositeCompetitor);
  //game.registerCompetitorType(&titForTatWithRandom);

  game.setCompetitors();
  game.play();
  game.output();
  return 0;
}
