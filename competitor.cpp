#include <cstdlib>
#include "competitor.h"

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

Choice TitForTatCompetitor::decision(int index)
{
  auto entry = history_.find( index );
  if ( entry  != history_.end() ) {
    return ( entry.value().back().second == COOPERATE ) ? COOPERATE: DEFECT;
  }
  return COOPERATE;
}

Choice RandomCompetitor::decision(int index)
{
  return ( qrand() > RAND_MAX / 2 ) ? DEFECT : COOPERATE;
};


Choice OppositeCompetitor::decision(int index)
{
  auto entry = history_.find( index );
  if ( entry != history_.end() ) {

    return ( entry.value().back().second == COOPERATE ) ? DEFECT : COOPERATE;
  }
  return ( qrand() > RAND_MAX / 2 ) ? DEFECT : COOPERATE;
}
