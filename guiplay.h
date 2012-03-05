#ifndef GAMELAYOUT_H
#define GAMELAYOUT_H

#include <vector>
#include <map>
#include <QWidget>
#include <QVector>
#include "common.h"

class Game;
class QPushButton;
class QTimer;
class CompetitorWidget;

using namespace std;

class GuiPlay: public QWidget
{
  Q_OBJECT
public:
  explicit GuiPlay(Game& game,
                   DisplayMethodology displayMethodology,
                   map < QString, QColor >& colors, QWidget *parent = 0);

signals:
  void runRound(int, int, bool);

public slots:
  void startPlaying();
  void executeRound();

private:
  QTimer* timeBetweenRounds_;
  Game& game_;
  QVector<CompetitorWidget*> competitorWidgets_;
  int timerCount_;
};

#endif // GAMELAYOUT_H
