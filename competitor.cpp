#include <cstdlib>
#include <QString>
#include "common.h"
#include "competitor.h"
#include "game.h"

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

void Competitor::setGame(const Game* game)
{
  game_ = game;
}

const Game* Competitor::getGame() const
{
  return game_;
}


REGISTER_COMPETITOR( TitForTat );
REGISTER_COMPETITOR( AlwaysDefect );
REGISTER_COMPETITOR( Random );
REGISTER_COMPETITOR( AlwaysCooperate );
REGISTER_COMPETITOR( Opposite );
REGISTER_COMPETITOR( TitForTatRandom );

Choice TitForTat::decision(int index) const
{
  auto entry = history_.find( index );
  if ( entry  != history_.end() ) {
    return ( entry.value().back().second == COOPERATE ) ? COOPERATE: DEFECT;
  }
  return COOPERATE;
}

Choice TitForTatRandom::decision(int index) const
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

Choice AlwaysCooperate::decision(int) const {
  return COOPERATE;
};

Choice AlwaysDefect::decision(int) const {
  return DEFECT;
};


Choice Random::decision(int ) const
{
  return ( drand() > 0.5 ) ? DEFECT : COOPERATE;
};


Choice Opposite::decision(int index) const
{
  auto entry = history_.find( index );
  if ( entry != history_.end() ) {

    return ( entry.value().back().second == COOPERATE ) ? DEFECT : COOPERATE;
  }
  return ( drand() > 0.5 ) ? DEFECT : COOPERATE;
}

