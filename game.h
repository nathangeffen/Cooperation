#ifndef GAME_H
#define GAME_H

#include <QtCore>
#include "competitor.h"

class Game {
public:
  Game();
  void setIterations(int nIterations) { nIterations_ = nIterations; }
  void registerCompetitorType( Competitor* competitor );
  void addCompetitor( const competitor_ptr& competitor );
  void setCompetitors();
  void setRandomSeed( int randomSeed );
  void shuffleCompetitors();
  int getNumberCompetitors() { return nCompetitors_; };
  Competitor& getCompetitor( int i ) {return *competitors_[i]; };
  void play( bool print_contests_csv = true );
  void output() const;

private:

  void init();
  int nIterations_;
  int nCompetitors_;
  QVector < Competitor* > competitorTypes_;
  QVector < competitor_ptr > competitors_;
  QVector < int > generateRandomIndices() const;
  QMap < QPair < Choice, Choice >, QPair < int, int > > choiceTable_;
};

#endif // GAME_H
