#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QPainter>

class Competitor;
class QLabel;

class CompetitorWidget: public QWidget
{
  Q_OBJECT

public:
  CompetitorWidget(int circleSize, Competitor& competitor, QWidget *parent = 0);
  void setMaxScore( int max_score ) { maxScore_ = max_score; };
  void setMinScore( int min_score ) { minScore_ = min_score; };
public slots:
  void recalc(int min_score, int max_score) {
    setMinScore(min_score);
    setMaxScore(max_score);
    update();
  }
protected:
  void paintEvent(QPaintEvent *);
private:
  int circleSize_;
  QLabel *label;
  QColor color_;
  Competitor& competitor_;
  int maxScore_;
  int minScore_;
};

#endif // PLAYER_H
