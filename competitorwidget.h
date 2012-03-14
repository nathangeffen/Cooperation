#ifndef PLAYER_H
#define PLAYER_H

#include <QtGui>
#include "common.h"

class Competitor;
class QLabel;
class QHBoxLayout;
class QGridLayout;
class CompetitorShape;

class CompetitorWidget: public QWidget
{
  Q_OBJECT

public:
  CompetitorWidget(int circleSize, Competitor& competitor,
                   DisplayMethodology displayMethodology, QColor color, QWidget *parent = 0);
  void setMaxScore( int max_score ) { maxScore_ = max_score; }
  void setMinScore( int min_score ) { minScore_ = min_score; }
  void updateUsingRatio();
  void updateUsingRank();
  void updateUsingRationNormalizedToZero();

signals:
   void sendUpdate();
public slots:
  void executeUpdate(int min_score, int max_score, bool updateScore);

private:
  Competitor& competitor_;
  CompetitorShape* competitorShape_;
  QHBoxLayout *topline_;
  QGridLayout *layout_;
  QLabel *nameLabel_;
  QLabel *scoreLabel_;
  int maxDiameter_;
  int maxScore_;
  int minScore_;
  int savedScore_;
  bool updateScore_;
  DisplayMethodology displayMethodology_;
  QColor color_;
};

#endif // PLAYER_H
