#include <cstdlib>
#include "common.h"
#include "competitor.h"

const char* TITFORTAT = "titfortat";
const char* ALWAYSDEFECT = "alwaysdefect";
const char* ALWAYSCOOP = "alwayscoop";
const char* RANDOM = "random";
const char* TITFORTATRAND = "titfortatwithrandom";
const char* OPPOSITE = "opposite";


Competitor::Competitor()
{
  score_ = 0;
}


void Competitor::recordChoices(Choice myChoice,
                               int opponentIndex,
                               Choice opponentChoice)
{
  history_[opponentIndex].push_back(
            qMakePair(myChoice, opponentChoice)
          );
}

Choice TitForTatCompetitor::decision(int index) const
{
  auto entry = history_.find( index );
  if ( entry  != history_.end() ) {
    return ( entry.value().back().second == COOPERATE ) ? COOPERATE: DEFECT;
  }
  return COOPERATE;
}

Choice TitForTatWithRandomCompetitor::decision(int index) const
{
  auto entry = history_.find( index );
  if ( entry  != history_.end() ) {
    if ( drand() > 0.9 ) {
      return ( entry.value().back().second == COOPERATE ) ? COOPERATE: DEFECT;
    } else {
      return ( entry.value().back().second == DEFECT ) ? COOPERATE: DEFECT;
    }
  }
  return COOPERATE;
}

Choice RandomCompetitor::decision(int ) const
{
  return ( drand() > 0.5 ) ? DEFECT : COOPERATE;
};


Choice OppositeCompetitor::decision(int index) const
{
  auto entry = history_.find( index );
  if ( entry != history_.end() ) {

    return ( entry.value().back().second == COOPERATE ) ? DEFECT : COOPERATE;
  }
  return ( drand() > 0.5 ) ? DEFECT : COOPERATE;
}
