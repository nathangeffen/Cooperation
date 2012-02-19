#ifndef GAMELAYOUT_H
#define GAMELAYOUT_H

#include <QDebug>
#include <QWidget>
#include <QVector>

class Game;
class QPushButton;
class QTimer;
class CompetitorWidget;

class GuiPlay: public QWidget
{
  Q_OBJECT
public:
  explicit GuiPlay(Game& game, QWidget *parent = 0);

signals:
  void runRound(int, int);

public slots:
  void startPlaying();
  void executeRound();

private:
  QTimer *timeBetweenRounds_;
  Game& game_;
  QPushButton *playGame_;
  QVector<CompetitorWidget*> competitorWidgets_;
  int timerCount_;
};

#endif // GAMELAYOUT_H
