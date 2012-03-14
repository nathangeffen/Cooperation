#ifndef GAMELAYOUT_H
#define GAMELAYOUT_H

#include <vector>
#include <map>
#include <QtGui>
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
  GuiPlay(Game& game, DisplayMethodology displayMethodology,
          int time, int updateFrequency, map < QString, QColor >& colors,
          QWidget *parent = 0);
  void pausePlaying();
  bool isPaused() { return paused_; }
  QProgressBar* getProgressBar() const { return progressBar_; }

signals:
  void runRound(int, int, bool);
  void signalStartPlaying();
  void stopPlaying();

public slots:
  void startPlaying();
  void executeRound();

private:
  QTimer* timeBetweenRounds_;
  QProgressBar* progressBar_;
  Game& game_;
  QVector<CompetitorWidget*> competitorWidgets_;
  int timerCount_;
  int time_;
  int updateFrequency_;
  bool paused_;
  bool stopped_;
};

#endif // GAMELAYOUT_H
