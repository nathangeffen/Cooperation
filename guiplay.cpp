#include <QApplication>
#include <QObject>
#include <QtGui>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>

#include "guiplay.h"
#include "game/game.h"
#include "competitorwidget.h"
#include "game/common.h"

GuiPlay::GuiPlay(Game& game, DisplayMethodology displayMethodology,
                 int time, int updateFrequency, map < QString, QColor >& colors,
                 QWidget *parent)
  : QWidget(parent), game_(game), time_(time), updateFrequency_(updateFrequency)
{
  QGridLayout *playerSection = new QGridLayout( this );
  setLayout(playerSection);
  paused_ = true;
  stopped_ = true;

  timeBetweenRounds_ = new QTimer(this);
  progressBar_ = new QProgressBar( this );
  progressBar_->setVisible( false );
  connect(timeBetweenRounds_, SIGNAL(timeout()), this, SLOT(executeRound()));

  int square;
  for (square = 0; square * square < game_.getNumberCompetitors(); square++ );

  int max_height = this->geometry().height() - 100;
  int circleSize = max_height / square;

  int counter = 0;
  for ( int i=0; i < square && counter < game_.getNumberCompetitors(); i++ ) {
    for (int j = 0; j < square && counter < game_.getNumberCompetitors(); j++) {
      QColor color = colors[ game_.getCompetitor(counter).output() ];
      CompetitorWidget *competitorWidget = new
          CompetitorWidget( circleSize, game_.getCompetitor(counter),
                            displayMethodology, color);
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
  progressBar_->reset();
  progressBar_->setOrientation(Qt::Horizontal);
  progressBar_->setRange(0, game_.getIterations() );
  progressBar_->setVisible( true );
  timerCount_ = 0;
  paused_ = false;
  stopped_ = false;
  timeBetweenRounds_->start();
}

void GuiPlay::pausePlaying()
{
  if ( timeBetweenRounds_->isActive()  ) {
    paused_ = true;
    timeBetweenRounds_->stop();
  }
  else {
    paused_ = false;
    timeBetweenRounds_->start(time_);
  }
}

void GuiPlay::executeRound()
{
  if ( timerCount_ < game_.getIterations() ) {
    game_.executeRound();
    bool updateScore = timerCount_ % 500 == 0 ||
                       timerCount_ == game_.getIterations() - 1;
    if ( timerCount_ % updateFrequency_ == 0 ) {
      runRound( game_.minScore(), game_.maxScore(), updateScore );
    }
    ++timerCount_;
    progressBar_->setValue( timerCount_ );
  } else {
    timeBetweenRounds_->stop();
    paused_ = false;
    stopped_ = true;
    emit stopPlaying();
  }
}

