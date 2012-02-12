#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <iostream>
#include <memory>
#include <QtCore>

extern const char* TITFORTAT;
extern const char* ALWAYSDEFECT;
extern const char* ALWAYSCOOP;
extern const char* RANDOM;
extern const char* TITFORTATRAND;
extern const char* OPPOSITE;


enum Choice {
  DEFECT,
  COOPERATE
};

class Competitor {
public:
  Competitor();
  void setScore( int score ) { score_ = score; };
  void changeScore( int score ) { score_ += score; };
  int getScore() const {return score_;};
  int operator() () const { return getScore(); };
  virtual Choice decision(int competitorIndex) const = 0;
  void recordChoices(Choice myChoice,
                     int opponentIndex,
                     Choice opponentChoice);
  virtual std::shared_ptr< Competitor >  create() const = 0;
  virtual QString output() const { return "Competitor"; };

protected:
  // This is a map from opponents to a vector of choices made by this competitor
  // and its opponents.
  QMap <int, QVector <QPair <Choice, Choice> > > history_;

private:
  double score_;
};

typedef std::shared_ptr< Competitor > competitor_ptr;

class TitForTatCompetitor : public Competitor {
public:
  virtual Choice decision(int index) const;
  virtual competitor_ptr create() const {
    return competitor_ptr( new TitForTatCompetitor );
  };
  virtual QString output() const {return "Tit for Tat"; };
};

class AlwaysDefectCompetitor : public Competitor {
public:
  virtual Choice decision(int ) const {return DEFECT;};
  virtual competitor_ptr create() const {
    return competitor_ptr( new AlwaysDefectCompetitor );
  };
  virtual QString output() const {return "Always Defect"; };
};

class RandomCompetitor : public Competitor {
public:
  virtual Choice decision(int index) const;
  virtual competitor_ptr  create() const {
    return competitor_ptr ( new RandomCompetitor );
  };
  virtual QString output() const {return "Random"; };
};

class AlwaysCooperateCompetitor : public Competitor {
public:
  virtual Choice decision(int ) const {return COOPERATE;};
  virtual competitor_ptr  create() const {
    return competitor_ptr ( new AlwaysCooperateCompetitor );
  };
  virtual QString output() const {return "Always Co-operate"; };
};

class OppositeCompetitor : public Competitor {
public:
  virtual Choice decision(int index) const;
  virtual competitor_ptr  create() const {
    return competitor_ptr ( new OppositeCompetitor );
  };
  virtual QString output() const {return "Opposite"; };
};

class TitForTatWithRandomCompetitor : public Competitor {
public:
  virtual Choice decision(int index) const;
  virtual competitor_ptr  create() const {
    return competitor_ptr ( new TitForTatWithRandomCompetitor );
  };
  virtual QString output() const {return "Tit for Tat with Random"; };
};

#endif // COMPETITOR_H
