#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <fstream>

#include <QtGui>

#include "guicommon.h"
#include "game/game.h"

class GuiPlay;

/** Main window of the GUI.
  */

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  /** Every main window keeps an instance of a Game that is passed to the
    * constructor.
    */
  MainWindow( Game& game );

  /** Change the main window's game instance.
    */
  void setGame(Game& game) { game_ = game; }

  /** Retrieve the main window's game instance.
    */
  Game& getGame() const { return game_; }

private slots:
  void openGameDefinition();
  void saveGameDefinition();

  void newGameDialog();
  void executeGame();
  void pauseGame();
  void stopPlaying();

private:
  bool inProgress_;

  Game& game_;
  QMenu* fileMenu_;
  QMenu* gameMenu_;
  GuiPlay* guiPlay_;

  QTextEdit* helpText_;

  QIcon openGameIcon_;
  QIcon saveGameIcon_;
  QIcon newGameIcon_;
  QIcon playIcon_;
  QIcon pauseIcon_;

  QAction* openGameAction_;
  QAction* saveGameAction_;
  QAction* newGameAction_;
  QAction* playAction_;

  QToolBar* toolBar_;

  QProgressBar* progressBar_;


  DisplayMethodology displayMethodology_;
  int updateFrequency_;
  int timer_;
  bool firstTime_;
  map <QString, QColor > colors_;
  std::streambuf *outputBuffer_, *coutBackup_;
  std::ofstream outputFile_;

  void setPlayActionToPlay( bool enabled = true );
  void setPlayActionToPause( bool enabled = false );
  void drawGameGrid();
  void setupToolBar();
  void redirectCout();
  void resetCout();
};

#endif // MAINWINDOW_H
