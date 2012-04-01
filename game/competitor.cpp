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
REGISTER_COMPETITOR( Pavlov );

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

Choice Pavlov::decision( int index ) const
{
  auto entry = history_.find( index );
  if ( entry  != history_.end() ) {
    if ( entry.value().back().first != entry.value().back().second )
      return DEFECT;
    else
      return entry.value().back().first;
  }
  return COOPERATE;
}
