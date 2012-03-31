#include <QApplication>
#include <QObject>
#include <QtGui>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>

#include "game/game.h"
#include "gui.h"
#include "competitorwidget.h"
#include "mainwindow.h"
#include "game/common.h"


Gui::Gui( Game& game ) : game_(game) {}

int Gui::start()
{
  int argc = 0;
  char *argv[] = {};
  QApplication app(argc, argv);
  MainWindow mainWindow( game_ );

  mainWindow.showMaximized();

  return app.exec();
}

