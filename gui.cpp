/* This source file is part of Cooperation, an implementation of the 
 * Prisoner's Dilemna game.
 *
 * Copyright (C) 2012 by Nathan Geffen 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

