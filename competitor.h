#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <QtCore>

enum Choice {
  DEFECT,
  COOPERATE
};

class Competitor {
public:
  Competitor();
  void setScore(int score) { score_ = score; };
  void changeScore(int score) {
    score_ += score;
  };
  int getScore() const {return score_;};
  virtual Choice decision(int competitorIndex) {return DEFECT; };
  void recordChoices(Choice myChoice,
                     int opponentIndex,
                     Choice opponentChoice);
  //QVector< ChoicePair >& getChoicePair(int competitorIndex) {return history_[0];};
  virtual Competitor* copyTo() {return new Competitor; };
  virtual QString output() { return "Competitor"; };

protected:
  // This is a map from opponents to a vector of choices made by this competitor
  // and its opponents.
  QMap <int, QVector <QPair <Choice, Choice> > > history_;

private:
  double score_;
};

class TitForTatCompetitor : public Competitor {
public:
  virtual Choice decision(int index);
  virtual Competitor* copyTo() {return new TitForTatCompetitor; };
  virtual QString output() {return "Tit for Tat"; };
};

class AlwaysDefectCompetitor : public Competitor {
public:
  virtual Choice decision(int index) {return DEFECT;};
  virtual Competitor* copyTo() {return new AlwaysDefectCompetitor; };
  virtual QString output() {return "Always Defect"; };
};

class RandomCompetitor : public Competitor {
public:
  virtual Choice decision(int index);
  virtual Competitor* copyTo() {return new RandomCompetitor; };
  virtual QString output() {return "Random"; };
};

class AlwaysCooperateCompetitor : public Competitor {
public:
  virtual Choice decision(int index) {return COOPERATE;};
  virtual Competitor* copyTo() {return new AlwaysCooperateCompetitor; };
  virtual QString output() {return "Always Co-operate"; };
};

class OppositeCompetitor : public Competitor {
public:
  virtual Choice decision(int index);
  virtual Competitor* copyTo() {return new OppositeCompetitor; };
  virtual QString output() {return "Opposite"; };
};

class TitForTatWithRandom : public Competitor {
public:
  virtual Choice decision(int index) {return DEFECT;};
  virtual Competitor* copyTo() {return new TitForTatWithRandom; };
  virtual QString output() {return "Tit for Tat with Random"; };
};

#endif // COMPETITOR_H
