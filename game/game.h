#ifndef GAME_H
#define GAME_H

#include <QtCore>
#include <vector>
#include "competitor.h"

using namespace std;

/** This class controls the play of the Prisoner's Dilemna game.
  */

class Game {
public:
  Game();

  /** Sets the number of times the game will iterate.
    */
  void setIterations(int nIterations) { nIterations_ = nIterations; }

  /** New competitor types must be registered with the game using this method.
    */
  void registerCompetitorType( Competitor* competitor );

  /** Adds a single competitor to the game.
    */
  void addCompetitor( const competitor_ptr& competitor );

  /** Adds n competitors for each n in a vector of integers where each
    * entry corresponds to a competitor type in the global registeredCompetitors
    * map.
    */
  void setCompetitors( const vector <int>& nCompetitors );

  /** Adds n competitors for each n in a map of strings and integers where each
    * string has an entry in the registeredCompetitors map.
    */
  void setCompetitors( const map<string, int>& nCompetitorsMap );

  /** Sets a random seed used in the simulation.
    */
  void setRandomSeed( int randomSeed );

  /** Shuffles the competitors before the game begins.
    */
  void shuffleCompetitors();


  /** Returns the total number of competitors
    */
  int getNumberCompetitors() const { return nCompetitors_; }

  /** Returns a map of competitor names and the number of competitors corresponding
    * to each name.
    *
    * Each competitor name must be in the global registeredCompetitors map.
    */
  map<QString, int> getNumberCompetitorsPerCompetitor() const { return numberCompetitorsMap_; }

  /** Gets the competitor with the given index.
    *
    * Each competitor is associated with a unique non-negative integer index
    */
  Competitor& getCompetitor( int i ) const {return *competitors_[i]; }

  /** Plays one round of Prisoner's Dilemna.
    *
    * @param[in] print_contests_csv whether or not to print, in csv format, the
    *            result of each match to standard output.
    *
    * This works as follows:
    * <ul>
    * <li> The players are randomly shuffled.</li>
    * <li> Each player is paired against the player adjacent to it.</li>
    * <li> The decision function of each of the matched players is called. </li>
    * <li> Scores are calculated and tracked. </li>
    * </ul>
    *
    */
  void executeRound( bool print_contests_csv = true );

  /** Plays a full game of Prisoner's Dilemna, ie executeRound is called
    * getIterations() times.
    *
    * @param[in] print_contests_csv whether or not to print, in csv format, the
    *            result of each match to standard output.
    */
  void play( bool print_contests_csv = true );

  /** Prints to standard output the csv header that is
    * used for printing the results of matches.
    */
  void csvHeader();

  /** Returns the number of iterations the game will run for.
    *
    * See setIterations()
    *
    */
  int getIterations() const { return nIterations_; }

  /** Returns the score of the worst player.
    */
  int minScore() const;

  /** Returns the score of the best player.
    */
  int maxScore() const;

  /** Generates statistical information about the game.
    */
  void output() const;

  /** Calculates the rank in the competition of the given score.
    *
    * @param[in] score the score to calculate the rank for.
    *
    * The lower the rank, the better the player has done. The top players'
    * scores will have a rank of zero. If two or more players have the same
    * score they will have the same rank.
    *
    */
  int getRank(int score) const;

  /** Returns the random seed.
    */
  int getRandomSeed() const;

  /** Initiates the game.
    *
    * This is called by the constructor. But it will also need to be called
    * if the same instance of a Game object is to be used for a new game.
    */
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
