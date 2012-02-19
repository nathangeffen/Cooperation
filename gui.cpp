#include <QApplication>
#include <QObject>
#include <QtGui>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>

#include "game.h"
#include "gui.h"
#include "competitorwidget.h"
#include "guiplay.h"


Gui::Gui( Game& game ) : game_(game) {}

int Gui::start()
{
  int argc = 0;
  char *argv[] = {};
  QApplication app(argc, argv);
  GuiPlay guiplay(game_);
  guiplay.show();

  return app.exec();
}

