#ifndef GAME_H
#define GAME_H

#include <QtCore>
#include "competitor.h"


class Game {
public:
  Game( int nIterations = 100, int nCompetitors = 100 );
  void registerCompetitorType( Competitor* competitor );
  void setCompetitors();
  void play();
  void chooseCompetitors();
  void executeCompetitorDecision(Competitor& competitor);
  void output();

private:
  int nIterations_;
  int nCompetitors_;
  QVector <Competitor*> competitorTypes_;
  QVector <Competitor*> competitors_;
  QVector <int> generateRandomIndices();
  QMap < QPair < Choice, Choice >, QPair < int, int > > choiceTable_;
};

#endif // GAME_H
