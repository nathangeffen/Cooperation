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
#include "common.h"


Gui::Gui( Game& game, DisplayMethodology displayMethodology ) : game_(game),
  displayMethodology_(displayMethodology) {}

int Gui::start()
{
  int argc = 0;
  char *argv[] = {};
  QApplication app(argc, argv);
  GuiPlay guiplay(game_, displayMethodology_);
  guiplay.show();

  return app.exec();
}

