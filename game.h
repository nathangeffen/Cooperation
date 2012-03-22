#ifndef GAME_H
#define GAME_H

#include <QtCore>
#include <vector>
#include "competitor.h"

using namespace std;

class Game {
public:
  Game();
  void setIterations(int nIterations) { nIterations_ = nIterations; }
  void registerCompetitorType( Competitor* competitor );
  void addCompetitor( const competitor_ptr& competitor );
  void setCompetitors( const vector <int>& nCompetitors );
  void setCompetitors( const map<string, int>& nCompetitorsMap );
  void setRandomSeed( int randomSeed );
  void shuffleCompetitors();
  int getNumberCompetitors() const { return nCompetitors_; }
  map<QString, int> getNumberCompetitorsPerCompetitor() const { return numberCompetitorsMap_; }
  Competitor& getCompetitor( int i ) const {return *competitors_[i]; }
  void executeRound( bool print_contests_csv = true );
  void play( bool print_contests_csv = true );
  void csvHeader();
  int getIterations() const { return nIterations_; }
  int minScore() const;
  int maxScore() const;
  void output() const;
  int getRank(int score) const;
  int getRandomSeed() const;
  void init();


private:

  int nIterations_;
  int nCompetitors_;
  int randomSeed_;
  QVector < Competitor* > competitorTypes_;
  QVector < competitor_ptr > competitors_;
  QVector < int > generateRandomIndices() const;
  QMap < QPair < Choice, Choice >, QPair < int, int > > choiceTable_;
  map < QString, int >  numberCompetitorsMap_;
};

#endif // GAME_H
