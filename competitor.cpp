#include <cstdlib>
#include <QString>
#include "common.h"
#include "competitor.h"

std::map < QString, competitor_ptr >  registeredCompetitors;

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

REGISTER_COMPETITOR_WITH_COLOR( TitForTatCompetitor, "red" );
REGISTER_COMPETITOR_WITH_COLOR( AlwaysDefectCompetitor, "black" );
REGISTER_COMPETITOR_WITH_COLOR( RandomCompetitor, "blue" );
REGISTER_COMPETITOR_WITH_COLOR( AlwaysCooperateCompetitor, "yellow" );
REGISTER_COMPETITOR_WITH_COLOR( OppositeCompetitor, "white" );
REGISTER_COMPETITOR_WITH_COLOR( TitForTatWithRandomCompetitor, "green" );

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

Choice AlwaysCooperateCompetitor::decision(int) const {
  return COOPERATE;
};

Choice AlwaysDefectCompetitor::decision(int) const {
  return DEFECT;
};


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
