#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <sstream>

#include <QtGui>
#include "common.h"
#include "game.h"

class GuiPlay;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow( Game& game );
  void setGame(Game& game) { game_ = game; }
  Game& getGame() const { return game_; }

private slots:
  void openGameDefinition();
  void saveGameDefinition();
  void saveGameOutput();

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

  QPixmap* openGamePixmap_;
  QPixmap* saveGamePixmap_;
  QPixmap* saveOutputPixmap_;
  QPixmap* newGamePixmap_;
  QPixmap* playPixmap_;
  QPixmap* pausePixmap_;

  QIcon* openGameIcon_;
  QIcon* saveGameIcon_;
  QIcon* saveOutputIcon_;
  QIcon* newGameIcon_;
  QIcon* playIcon_;
  QIcon* pauseIcon_;

  QAction* openGameAction_;
  QAction* saveGameAction_;
  QAction* saveOutputAction_;
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
  std::stringstream outputStream_;

  void setPlayActionToPlay( bool enabled = true );
  void setPlayActionToPause( bool enabled = false );
  void drawGameGrid();
  void setupToolBar();
  void redirectCout();
  void resetCout();
};

#endif // MAINWINDOW_H
