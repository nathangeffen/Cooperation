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

enum Choice {
  DEFECT,
  COOPERATE
};


class Competitor {
public:
  Competitor();
  void setScore( int score ) { score_ = score; }
  void changeScore( int score ) { score_ += score; }
  int getScore() const {return score_; }
  int operator() () const { return getScore(); }
  virtual Choice decision(int) const = 0;
  void recordChoices(Choice myChoice,
                     int opponentIndex,
                     Choice opponentChoice);
  virtual std::shared_ptr< Competitor >  create() const = 0;
  virtual QString output() const = 0;
  void setGame(const Game* game);
  const Game* getGame() const;

protected:
  // This is a map from opponents to a vector of choices made by this competitor
  // and its opponents.
  QMap <int, QVector <QPair <Choice, Choice> > > history_;

private:
  double score_;
  const Game* game_;
};

typedef std::shared_ptr< Competitor > competitor_ptr;

extern std::map < QString, competitor_ptr >  registeredCompetitors;

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
