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

private:
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

  DisplayMethodology displayMethodology_;
  int updateFrequency_;
  map <QString, QColor > colors_;

  void drawGameGrid();
  void createMenus();
  void createActions();
};

#endif // MAINWINDOW_H
