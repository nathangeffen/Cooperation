#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QPainter>

class CompetitorWidget: public QWidget
{
  Q_OBJECT

public:
  CompetitorWidget(int circleSize, QString = "red", QWidget *parent = 0);

protected:
  void paintEvent(QPaintEvent *);
private:
  int circleSize_;
  QColor color_;
};

#endif // PLAYER_H
