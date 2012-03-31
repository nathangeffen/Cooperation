#ifndef GAMELAYOUT_H
#define GAMELAYOUT_H

#include <vector>
#include <map>
#include <QtGui>
#include "guicommon.h"

class Game;
class QPushButton;
class QTimer;
class CompetitorWidget;

using namespace std;

/** Instances of this class play the game of Prisoner's Dilemna using the GUI.
  */

class GuiPlay: public QWidget
{
  Q_OBJECT
public:

  /** The constructor takes several parameters.
    *
    * @param[in] game a reference to an instance of Game class.
    * @param[in] displayMethodology the type of method used to display the
                 competitors int the GUI.
      @param[in] time time between iterations, usually to 0
      @param[in] updateFrequency specifies the number of iterations to execute
                 before updating the GUI, usually 1.
      @param[in] colors map from QString to QColor specifying the color for each
                 competitor type.

    */
  GuiPlay(Game& game, DisplayMethodology displayMethodology,
          int time, int updateFrequency, map < QString, QColor >& colors,
          QWidget *parent = 0);

  /** Pauses the game, usually when user toggles the play button on the GUI.
    */
  void pausePlaying();

  /** Checks if the game is paused.
    */
  bool isPaused() { return paused_; }

  /** Retrieves the progress bar used to indicate to the user how far the game
    * still have to go before completion.
    */
  QProgressBar* getProgressBar() const { return progressBar_; }

signals:

  /** When this is emitted, every competitor widget is updated.
    */
  void runRound(int, int, bool);

  /** Used the mainWindow as a signal to its stopPlaying slot.
    */
  void stopPlaying();

public slots:
  /** Slot that starts playing the game on the GUI.
    */
  void startPlaying();
  /** Plays one iteration of the game on the GUI.
    */
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
