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

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>

#include <QtGui>

#include "guiplay.h"
#include "mainwindow.h"
#include "definegamedialog.h"

using namespace std;

MainWindow::MainWindow(Game& game) : game_(game)
{
  setWindowTitle( tr("Prisoner's Dilemna") );

  updateFrequency_ = 1;
  displayMethodology_ = RANK;
  timer_ = 0;
  firstTime_ = true;

  QWidget *topFiller = new QWidget( this );
  topFiller->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

  statusBar()->showMessage(tr("Welcome to the Prisoner's Dilemna game"));

  uint colorStep = 0xFFFFFF / registeredCompetitors.size();
  uint i = 0;

  for ( auto c : registeredCompetitors ) {
    colors_[c.first] = QColor("#" + QString::number(i, 16).rightJustified(6, '0'));
    i += colorStep;
  }

  this->menuBar()->setVisible( false );

  inProgress_ = false;

  // Set up the toolbar, the actions on it and the icons for those actions

  setupToolBar();

  QString helpText = "<h1>Welcome to Cooperation</h1>\n"
    "<h2>An implementation of the Prisoner's Dilemna game</h2>\n"
    "<ul>\n"
    "<li><b>CTRL-n</b> Define a new game</li>\n"
    "<li><b>CTRL-o</b> Open a saved game definition</li>"
    "<li><b>CTRL-s</b> Save game definition (only active once a game has been defined)</li>\n"
    "<li><b>CTRL-p</b> Play a game (only active once a game has been defined or opened)</li>\n"
    "</ul>\n"
    "<p>Match results and game statistics are written to the logfile <i>prisonerslog.csv</i></p>\n"
    "<p>See the README file for more information.</p>"
    "<p>This software is still under development. It comes with absolutely no guarantees. "
    "If you want to help improve it please fork "
    "<a href='http://github.com/nathangeffen/Cooperation'>http://github.com/nathangeffen/Cooperation</p>"
    "<p>If you wish to learn more about the Prisoner's Dilemna game, here are some useful webpages:</p>"
    "<ul><li><a href='http://en.wikipedia.org/wiki/Prisoner%27s_Dilemna'>http://en.wikipedia.org/wiki/Prisoner%27s_Dilemna</a></li>"
    "<li><a href='http://plato.stanford.edu/entries/prisoner-dilemma'>http://plato.stanford.edu/entries/prisoner-dilemma</a></li>"
    "</ul>"
    "<p>Copyright (C) Nathan Geffen 2012. "
    "This is free software published under the "
    "GNU General Public License version 3.</p>"
    "<p>Send questions, queries and comments to nathangeffen at gmail.com</p>"
      ;
  helpText_ = new QTextEdit( helpText, this );
  helpText_->setReadOnly( true );
  setCentralWidget( helpText_ );
  guiPlay_ = 0;

  this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  setMinimumSize(160, 160);
  resize(480, 320);
}

void MainWindow::setupToolBar()
{
  toolBar_ = new QToolBar( this );

  openGameIcon_ = QIcon( QPixmap( ":/icons/open" ) );
  saveGameIcon_ = QIcon( QPixmap( ":/icons/savegame" ) );
  newGameIcon_ = QIcon( QPixmap( ":/icons/new" ) );
  playIcon_ = QIcon( QPixmap( ":/icons/play" ) );
  pauseIcon_ = QIcon( QPixmap( ":/icons/pause") );

  openGameAction_ = new QAction( openGameIcon_, QString(tr("Open")), this );
  openGameAction_->setShortcut( QKeySequence::Open );
  connect( openGameAction_, SIGNAL(triggered()), this, SLOT(openGameDefinition() ) );

  saveGameAction_ = new QAction( saveGameIcon_, QString(tr("Save game")), this );
  saveGameAction_->setShortcut( QKeySequence::Save );
  saveGameAction_->setDisabled( true );
  connect( saveGameAction_, SIGNAL(triggered()), this, SLOT(saveGameDefinition() ) );

  newGameAction_ = new QAction( newGameIcon_, QString(tr("New game")), this);
  newGameAction_->setShortcut( QKeySequence::New );

  playAction_ = new QAction( playIcon_, QString(tr("Play")), this );
  playAction_->setShortcut( QKeySequence( "CTRL+P") );
  playAction_->setDisabled( true );

  toolBar_->addAction( newGameAction_ );
  toolBar_->addAction( openGameAction_ );
  toolBar_->addAction( saveGameAction_ );

  connect( newGameAction_, SIGNAL(triggered()), this, SLOT(newGameDialog()) );
  toolBar_->addAction( playAction_ );

  addToolBar( toolBar_ );
}

void MainWindow::drawGameGrid()
{
  if ( game_.getNumberCompetitors() == 0 ) return;

  if ( guiPlay_ )
    delete guiPlay_;
  else
    connect(playAction_, SIGNAL(triggered() ), this, SLOT(executeGame() ) );

  playAction_->setEnabled( true );
  playAction_->setEnabled(true);
  guiPlay_ = new GuiPlay( game_, displayMethodology_, timer_,
                          updateFrequency_, colors_, this );
  connect(guiPlay_, SIGNAL( stopPlaying() ), this, SLOT(stopPlaying() ) );
  setCentralWidget( guiPlay_ );
}


void MainWindow::saveGameDefinition()
{
  if ( firstTime_ )
    return;

  QString filename;
  try {
    QFileDialog dialog( this );
    dialog.setFileMode( QFileDialog::AnyFile );
    dialog.setDefaultSuffix( QString("pdi") );
    dialog.setAcceptMode( QFileDialog::AcceptSave );
    dialog.setNameFilters( QStringList(QString("Game files (*.pdi)")) );

    if ( dialog.exec() ) {
      filename = dialog.selectedFiles()[0];
      ofstream out;
      out.exceptions(ios::failbit);
      out.open( filename.toStdString() );
      out << "numbercompetitors ";
      out << game_.getNumberCompetitorsPerCompetitor().size();
      for ( auto nCompetitors : game_.getNumberCompetitorsPerCompetitor() )
        out << " " << nCompetitors.first.toStdString() << " "
            << nCompetitors.second;
      out << endl;
      out << "iterations " << game_.getIterations() << endl;
      out << "randomseed " << game_.getRandomSeed() << endl;
      out << "updatefrequency " << updateFrequency_ << endl;
      out << "displaymethodology " << displayMethodology_ << endl;
      out << "competitorcolors ";
      for ( auto color : colors_ )
        out << " " << color.first.toStdString() << " "
            << color.second.name().toStdString();
      out << endl;
      out << "timer " << timer_ << endl;

      out.close();
      QMessageBox msgBox;
      msgBox.setText( tr("File successfully saved") );
      msgBox.exec();
    }
  } catch (exception &e) {
    QMessageBox msgBox;
    msgBox.setText( tr("Error writing to file: " ) +
                    QString( filename ) + QString("\n") );
    msgBox.exec();
  }
}

void MainWindow::openGameDefinition()
{
  QString filename;
  int value, nCompetitors;
  try {
    filename = QFileDialog::getOpenFileName (this,
                                             tr("Open file"),
                                             QDir::homePath(),
                                             "Game files (*.pdi)" );
    if ( !filename.compare("") ) return;
    game_.init();
    ifstream in;
    in.exceptions(ios::badbit);
    in.open( filename.toStdString() );
    string s;
    while ( in >> s ) {
      if ( s == "numbercompetitors" ) {
        in >> nCompetitors;
        if ( nCompetitors > 10000 || nCompetitors < 1 ) {
          throw string( "Number of competitors invalid." );
        }
        map <string, int> competitors;
        for ( int i = 0; i < nCompetitors; i++ ) {
          in >> s;
          in >> value;
          competitors[ s ] = value;
        }
        game_.setCompetitors( competitors );
      } else if ( s == "iterations" ) {
        in >> value;
        game_.setIterations( value );
      } else if ( s == "randomseed" ) {
        in >> value;
        game_.setRandomSeed( value );
      } else if ( s == "updatefrequency" ) {
        in >> updateFrequency_;
      } else if ( s == "displaymethodology" ) {
        in >> value;
        displayMethodology_ = DisplayMethodology( value );
      } else if ( s == "competitorcolors" ) {
        for ( int i = 0; i < nCompetitors; i++ ) {
          string stringColor;
          in >> s;
          in >> stringColor;
          colors_[ QString().fromStdString(s) ] =
              QColor( QString().fromStdString( stringColor ) );
        }
      } else if ( s == "timer" ) {
        if ( in >> value ) {
          timer_ = value;
        } else throw string("Invalid value for timer" );
      } else throw string("Unknown value: ") + s;
    }
    in.close();
    firstTime_ = false;
    game_.shuffleCompetitors();
    this->drawGameGrid();
  } catch (const string &s) {
    QMessageBox msgBox;
    msgBox.setText( QString().fromStdString(s) );
    msgBox.exec();
  } catch (exception &e) {
    QMessageBox msgBox;
    msgBox.setText( QString( tr("Error opening or reading from the file: " ) ) +
                    QString( filename ) + QString("\n") );
    msgBox.exec();
  }
}

void MainWindow::newGameDialog()
{
  DefineGameDialog* dialog = new DefineGameDialog( this );

  dialog->setIterations( game_.getIterations() );
  dialog->setRandomSeed( game_.getRandomSeed() );
  dialog->setUpdateFrequency( updateFrequency_ );
  dialog->setUpdateStyle( displayMethodology_ );
  dialog->setCompetitorColors( colors_ );
  dialog->setTimer( timer_ );
  dialog->setCompetitors( game_.getNumberCompetitorsPerCompetitor() );
  if ( firstTime_ ) {
    dialog->setNumberForAllCompetitors( 1 );
  }

  if ( dialog->exec() ) {
    if ( inProgress_ )
      this->stopPlaying();
    else
      firstTime_ = false;
    game_.init();
    game_.setIterations( dialog->getIterations() );
    game_.setRandomSeed( dialog->getRandomSeed() );
    updateFrequency_ = dialog->getUpdateFrequency();
    timer_ = dialog->getTimer();
    displayMethodology_ = (DisplayMethodology) dialog->getUpdateStyle();
    game_.setCompetitors( dialog->getCompetitors() );
    game_.shuffleCompetitors();
    colors_ = dialog->getCompetitorColors();
    saveGameAction_->setDisabled( false );
    drawGameGrid();
  }
}

void MainWindow::executeGame()
{
  inProgress_ = true;
  playAction_->setDisabled( true );
  setPlayActionToPause( true );
  progressBar_= guiPlay_->getProgressBar();
  this->statusBar()->addWidget( progressBar_ );
  redirectCout();
  game_.csvHeader();
  guiPlay_->startPlaying();
}

void MainWindow::redirectCout()
{
  coutBackup_ = cout.rdbuf();
  outputFile_.open("prisonerslog.csv");
  outputBuffer_= outputFile_.rdbuf();
  cout.rdbuf( outputBuffer_ );
}

void MainWindow::resetCout()
{
  cout.rdbuf( coutBackup_ );
  outputFile_.close();
}

void MainWindow::pauseGame()
{
  if ( guiPlay_ ) {
    if ( guiPlay_->isPaused() ) {
      setPlayActionToPause( true );
    }
    else {
      setPlayActionToPlay( true );
    }

    emit guiPlay_->pausePlaying();
  }
}

void MainWindow::stopPlaying()
{
  inProgress_ = false;
  statusBar()->removeWidget( progressBar_ );
  QString s = tr("Game finished after ") +
      QString().setNum( game_.getIterations() ) + tr( " iterations." );
  statusBar()->showMessage( s );
  setPlayActionToPlay( false);
  game_.output();
  resetCout();
}

void MainWindow::setPlayActionToPlay( bool enabled )
{
  playAction_->setIcon( playIcon_ );
  playAction_->setText( "&Play" );
  playAction_->setEnabled( enabled );
  playAction_->disconnect();
  if ( inProgress_ )
    connect( playAction_, SIGNAL(triggered()), this, SLOT(pauseGame()) );
  else
    connect( playAction_, SIGNAL(triggered()), this, SLOT(executeGame()) );
}

void MainWindow::setPlayActionToPause( bool enabled )
{
  playAction_->setIcon( pauseIcon_ );
  playAction_->setText( "&Pause" );
  playAction_->setEnabled( enabled );
  playAction_->disconnect();
  connect( playAction_, SIGNAL(triggered()), this, SLOT(pauseGame()) );
}
