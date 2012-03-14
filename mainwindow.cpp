#include <algorithm>
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


  QWidget *topFiller = new QWidget;
  topFiller->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

  statusBar()->showMessage(tr("Welcome to the Prisoner's Dilemna game"));

  uint colorStep = 0xFFFFFF / registeredCompetitors.size();
  uint i = 0;

  for ( auto c : registeredCompetitors ) {
    colors_[c.first] = QColor("#" + QString::number(i, 16).rightJustified(6, '0'));
    i += colorStep;
  }

  createActions();
  createMenus();

  inProgress_ = false;
  playPixmap_ = new QPixmap( ":/icons/arrow-right.xpm" );
  playIcon_ = new QIcon( *playPixmap_ );
  pausePixmap_ = new QPixmap( ":/icons/pause.xpm");
  pauseIcon_ = new QIcon( *pausePixmap_ );

  toolBar_ = new QToolBar( this );

  playAction_ = new QAction( *playIcon_, QString(tr("Play")), this );
  playAction_->setDisabled( true );
  toolBar_->addAction( playAction_ );
  addToolBar( toolBar_ );

  QWidget* widget = new QWidget;
  setCentralWidget( widget );
  guiPlay_ = 0;

  this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  setMinimumSize(160, 160);
  resize(480, 320);
}

void MainWindow::drawGameGrid()
{
  if ( game_.getNumberCompetitors() == 0 ) return;

  if ( guiPlay_ )
    delete guiPlay_;
  else
    connect(executeGame_, SIGNAL(triggered() ), this, SLOT(executeGame() ) );

  playAction_->setEnabled( true );
  executeGame_->setEnabled(true);
  pauseGame_->setDisabled(true);
  pauseGame_->setText( tr( "&Pause game" ) );
  guiPlay_ = new GuiPlay( game_, displayMethodology_, timer_,
                          updateFrequency_, colors_, this );
  connect(guiPlay_, SIGNAL( stopPlaying() ), this, SLOT(stopPlaying() ) );
  setCentralWidget( guiPlay_ );
}


void MainWindow::open()
{
  statusBar()->showMessage(tr("Open a game profile"));
}

void MainWindow::save()
{
  statusBar()->showMessage(tr("Save a game profile"));
}

void MainWindow::print()
{
  statusBar()->showMessage(tr("Print a game profile"));
}


void MainWindow::defineGameDialog()
{
  DefineGameDialog* dialog = new DefineGameDialog();

  dialog->setIterations( game_.getIterations() );
  dialog->setRandomSeed( game_.getRandomSeed() );
  dialog->setUpdateFrequency( updateFrequency_ );
  dialog->setUpdateStyle( displayMethodology_ );
  dialog->setCompetitorColors( colors_ );
  dialog->setTimer( timer_ );
  dialog->setCompetitors( game_.getNumberCompetitorsPerCompetitor() );
  if ( firstTime_ ) {
    firstTime_ = false;
    dialog->setNumberForAllCompetitors( 1 );
  }

  if ( dialog->exec() ) {
    game_.init();
    game_.setIterations( dialog->getIterations() );
    game_.setRandomSeed( dialog->getRandomSeed() );
    updateFrequency_ = dialog->getUpdateFrequency();
    timer_ = dialog->getTimer();
    displayMethodology_ = (DisplayMethodology) dialog->getUpdateStyle();
    game_.setCompetitors( dialog->getCompetitors() );
    game_.shuffleCompetitors();
    colors_ = dialog->getCompetitorColors();
    drawGameGrid();
  }
}

void MainWindow::executeGame()
{
  inProgress_ = true;
  executeGame_->setDisabled(true);
  pauseGame_->setEnabled(true);
  setPlayActionToPause( true );
  pauseGame_->setText( tr( "&Pause game" ) );
  progressBar_= guiPlay_->getProgressBar();
  this->statusBar()->addWidget( progressBar_ );
  guiPlay_->startPlaying();
}

void MainWindow::pauseGame()
{
  if ( guiPlay_ ) {
    if ( guiPlay_->isPaused() ) {
      pauseGame_->setText( tr( "&Pause game" ) );
      setPlayActionToPause( true );
    }
    else {
      pauseGame_->setText( tr( "Un&Pause game" ) );
      setPlayActionToPlay( true );
    }

    emit guiPlay_->pausePlaying();
  }
}

void MainWindow::createActions()
{

  openAct_ = new QAction(tr("&Open..."), this);
  openAct_->setShortcuts(QKeySequence::Open);
  openAct_->setStatusTip(tr("Open an existing game definition file"));
  connect(openAct_, SIGNAL(triggered()), this, SLOT(open()));

  saveAct_ = new QAction(tr("&Save"), this);
  saveAct_->setShortcuts(QKeySequence::Save);
  saveAct_->setStatusTip(tr("Save a game definition file to disk"));
  connect(saveAct_, SIGNAL(triggered()), this, SLOT(save()));

  printAct_ = new QAction(tr("&Print..."), this);
  printAct_->setShortcuts(QKeySequence::Print);
  printAct_->setStatusTip(tr("Print the game definition file"));
  connect(printAct_, SIGNAL(triggered()), this, SLOT(print()));

  exitAct_ = new QAction(tr("E&xit"), this);
  exitAct_->setShortcuts(QKeySequence::Quit);
  exitAct_->setStatusTip(tr("Exit Prisoner's Dilemna"));
  connect(exitAct_, SIGNAL(triggered()), this, SLOT(close()));

  defineGame_ = new QAction(tr("&Define game"), this);
  defineGame_->setStatusTip(tr("Define the parameters of a Prisoner's Dilemna game"));
  connect(defineGame_, SIGNAL(triggered()), this, SLOT(defineGameDialog()));

  executeGame_ = new QAction(tr("&Execute game"), this);
  executeGame_->setStatusTip(tr("Execute a Prisoner's Dilemna game"));
  executeGame_->setDisabled(true);
  connect(executeGame_, SIGNAL(triggered()), this, SLOT(executeGame()));

  pauseGame_ = new QAction(tr("&Pause game"), this);
  pauseGame_->setStatusTip(tr("Pause a Prisoner's Dilemna game"));
  pauseGame_->setDisabled(true);
  connect(pauseGame_, SIGNAL(triggered()), this, SLOT(pauseGame()));
}

void MainWindow::createMenus()
{
  fileMenu_ = menuBar()->addMenu(tr("&File"));
  fileMenu_->addAction(openAct_);
  fileMenu_->addAction(saveAct_);
  fileMenu_->addAction(printAct_);
  fileMenu_->addSeparator();
  fileMenu_->addAction(exitAct_);

  gameMenu_ = menuBar()->addMenu(tr("&Game"));
  gameMenu_->addAction(defineGame_);
  gameMenu_->addAction(executeGame_);
  gameMenu_->addAction(pauseGame_);
}

void MainWindow::stopPlaying()
{
  inProgress_ = false;
  statusBar()->removeWidget( progressBar_ );
  QString s = tr("Game finished after ") +
      QString().setNum( game_.getIterations() ) + tr( " iterations." );
  statusBar()->showMessage( s );
  setPlayActionToPlay( false);
}

void MainWindow::setPlayActionToPlay( bool enabled )
{
  playAction_->setIcon( *playIcon_ );
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
  playAction_->setIcon( *pauseIcon_ );
  playAction_->setText( "&Pause" );
  playAction_->setEnabled( enabled );
  playAction_->disconnect();
  connect( playAction_, SIGNAL(triggered()), this, SLOT(pauseGame()) );
}
