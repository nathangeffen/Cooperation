#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
  void open();
  void save();
  void print();

  void defineGameDialog();
  void executeGame();
  void pauseGame();
  void stopPlaying();

private:
  void setPlayActionToPlay( bool enabled = true );
  void setPlayActionToPause( bool enabled = false );
  bool inProgress_;

  Game& game_;
  QMenu* fileMenu_;
  QMenu* gameMenu_;
  GuiPlay* guiPlay_;

  QAction* openAct_;
  QAction* saveAct_;
  QAction* printAct_;
  QAction* exitAct_;

  QAction* defineGame_;
  QAction* executeGame_;
  QAction* pauseGame_;
  QProgressBar* progressBar_;
  QToolBar* toolBar_;
  QIcon* playIcon_;
  QIcon* pauseIcon_;
  QPixmap* playPixmap_;
  QPixmap* pausePixmap_;
  QAction* playAction_;

  DisplayMethodology displayMethodology_;
  int updateFrequency_;
  int timer_;
  bool firstTime_;
  map <QString, QColor > colors_;

  void drawGameGrid();
  void createMenus();
  void createActions();
};

#endif // MAINWINDOW_H
