#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <iostream>
#include <memory>
#include <vector>
#include <QString>
#include <utility>
#include <vector>
#include <QtCore>

class Game;

/** \enum : In the Prisoner's Dilemna game, you can either cooperate or defect.
  * This enum represents that choice.
  */

enum Choice {
  DEFECT,
  COOPERATE
};

/** This class implements the functionality of competitors in the
  * Prisoner's Dilemna game.
  *
  *  Each competitor subclasses this class. To declare a new type of competitor,
  *  use the macro REGISTER_COMPETITOR and implement the decision method.
  *
  *  Here is how the AlwaysDefect competitor is implemented.
  *
    <pre>
    REGISTER_COMPETITOR( AlwaysDefect );

    Choice AlwaysDefect::decision(int) const {
      return DEFECT;
    }
    </pre>
  */

class Competitor {
public:
  Competitor();

  /** Sets the score of the competitor to score.
    */
  void setScore( int score ) { score_ = score; }

  /** Changes the  score of a competitor by score.
   */
  void changeScore( int score ) { score_ += score; }

  /** Returns the score of a competitor.
    */
  int getScore() const {return score_; }

  /** Returns the score of a competitor.
    */
  int operator() () const { return getScore(); }

  /** This virtual abstract function implements the unique logic of a competitor.
    * Generally, this should be the only method re-implemented by competitors.
    *
    */
  virtual Choice decision(int) const = 0;

  /** Records this competitor's choice and the opponent's choice in every match.
    */
  void recordChoices(Choice myChoice,
                     int opponentIndex,
                     Choice opponentChoice);

  /** Dynamically creates this competitor on the heap.
    */
  virtual std::shared_ptr< Competitor >  create() const = 0;

  /** Returns the name of the Competitor type.
    */
  virtual QString output() const = 0;

  /** Let's this competitor know which game it is part of.
    */
  void setGame(const Game* game);

  /** Returns the game to which the competitor is attached.
    */
  const Game* getGame() const;

protected:
  /** This is a map from opponents to a vector of choices made by this competitor
    * and its opponents.
    */
  QMap <int, QVector <QPair <Choice, Choice> > > history_;

private:
  double score_;
  const Game* game_;
};

typedef std::shared_ptr< Competitor > competitor_ptr;

/** Global map storing the name of each competitor and a shared pointer to an
  * instance of it.
  */

extern std::map < QString, competitor_ptr >  registeredCompetitors;

/** Macro to register a new competitor type.
  */

#define REGISTER_COMPETITOR( X ) \
  class X : public Competitor { \
  public: \
  X ( bool registerCompetitor = false ) : \
      Competitor() { \
        if ( registerCompetitor ) { \
          registeredCompetitors[ this->output() ] = this->create(); \
        } \
     }; \
    virtual Choice decision(int index) const; \
    virtual competitor_ptr  create() const { \
      return competitor_ptr ( new X ); \
    }; \
    virtual QString output() const { return QString(#X).toLower(); }; \
  }; \
  X _ ## X (true)

#endif // COMPETITOR_H
