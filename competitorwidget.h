#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

class Competitor;
class QLabel;
class QVBoxLayout;

class CompetitorWidget: public QWidget
{
  Q_OBJECT

public:
  CompetitorWidget(int circleSize, Competitor& competitor, QWidget *parent = 0);
  void setMaxScore( int max_score ) { maxScore_ = max_score; };
  void setMinScore( int min_score ) { minScore_ = min_score; };
public slots:
  void recalc(int min_score, int max_score, bool updateScore) {
    setMinScore(min_score);
    setMaxScore(max_score);
    updateScore_ = updateScore;
    update();
  }
protected:
  void paintEvent(QPaintEvent *);
private:
  QColor color_;
  Competitor& competitor_;
  QVBoxLayout *layout_;
  QLabel *nameLabel_;
  QLabel *scoreLabel_;
  int maxCircleSize_;
  int maxScore_;
  int minScore_;
  int savedScore_;
  bool updateScore_;
};

#endif // PLAYER_H
