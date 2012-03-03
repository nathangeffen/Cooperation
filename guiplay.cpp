#include <QApplication>
#include <QObject>
#include <QtGui>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>

#include "guiplay.h"
#include "game.h"
#include "competitorwidget.h"
#include "common.h"

GuiPlay::GuiPlay(Game& game, DisplayMethodology displayMethodology, QWidget *parent)
  : QWidget(parent), game_(game)
{
  setWindowTitle(tr("Prisoner's Dilemna"));

  QPushButton *quit = new QPushButton(tr("&Quit"));
  quit->setFont(QFont("Times", 12, QFont::Bold));
  connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

  playGame_ = new QPushButton(tr("&Play"));
  playGame_->setFont(QFont("Times", 12, QFont::Bold));
  connect(playGame_, SIGNAL(clicked()), this, SLOT(startPlaying()));

  QGridLayout *playerSection = new QGridLayout;
  QGridLayout *topLayout = new QGridLayout;

  QGridLayout *menuLayout = new QGridLayout;
  menuLayout->addWidget(playGame_, 0, 0);
  menuLayout->addWidget(quit, 0, 1);
  topLayout->addLayout(menuLayout, 0, 0);
  topLayout->addLayout(playerSection, 1, 0);
  setLayout(topLayout);
  QRect screenSize = QApplication::desktop()->availableGeometry();
  this->setGeometry(screenSize);

  timeBetweenRounds_ = new QTimer(this);
  connect(timeBetweenRounds_, SIGNAL(timeout()), this, SLOT(executeRound()));

  int square;
  for (square = 0; square * square < game_.getNumberCompetitors(); square++ );

  int max_height = this->geometry().height() - 100;
  int circleSize = max_height / square;

  int counter = 0;
  for ( int i=0; i < square && counter < game_.getNumberCompetitors(); i++ ) {
    for (int j = 0; j < square && counter < game_.getNumberCompetitors(); j++) {
      CompetitorWidget *competitorWidget = new
          CompetitorWidget( circleSize, game_.getCompetitor(counter),
                            displayMethodology);
      playerSection->addWidget(competitorWidget, i, j);
      connect(this, SIGNAL(runRound(int, int, bool)),
              competitorWidget, SLOT(executeUpdate(int, int, bool)));
      competitorWidgets_.push_back(competitorWidget);
      ++counter;
    }
  }
}

void GuiPlay::startPlaying()
{
  if ( timeBetweenRounds_->isActive() ) {
    return;
  }
  playGame_->setDisabled(true);
  timerCount_ = 0;
  timeBetweenRounds_->start(0);
}

void GuiPlay::executeRound() {

  if ( timerCount_ < game_.getIterations() ) {
    game_.executeRound();
    bool updateScore = timerCount_ % 500 == 0 ||
                       timerCount_ == game_.getIterations() - 1;
    runRound( game_.minScore(), game_.maxScore(), updateScore );
    ++timerCount_;
  } else {
    timeBetweenRounds_->stop();
    playGame_->setDisabled(false);
  }
}

