#include <cmath>
#include <QGridLayout>
#include <QLabel>
#include "game.h"
#include "competitor.h"
#include "competitorwidget.h"
#include "competitorshape.h"
#include "common.h"

CompetitorWidget::CompetitorWidget(int maxDiameter, Competitor& competitor,
                                   DisplayMethodology displayMethodology,
                                   QColor color, QWidget *parent) :
  QWidget(parent), competitor_(competitor),
  maxDiameter_(maxDiameter ), maxScore_(0), savedScore_(0),
  displayMethodology_(displayMethodology), color_(color)
{
  nameLabel_ = new QLabel( competitor_.output().toUpper() );
  QFont font = nameLabel_->font();
  font.setPointSize(6);

  nameLabel_->setFont(font);

  scoreLabel_ = new QLabel( QString().setNum(0) );
  scoreLabel_->setFont(font);

  topline_ = new QHBoxLayout;
  topline_->addWidget(nameLabel_);
  topline_->addWidget(scoreLabel_);

  layout_ = new QGridLayout;
  layout_->addLayout(topline_, 0, 0);

  competitorShape_ = new CompetitorShape(maxDiameter / 6,
                                         color_);
  layout_->addWidget(competitorShape_, 1, 0);
  layout_->setSpacing(0);

  connect(this, SIGNAL(sendUpdate()),
          competitorShape_, SLOT(executeUpdate()));

  setLayout(layout_);
}

void CompetitorWidget::executeUpdate(int min_score,
                                     int max_score,
                                     bool updateScore)
{

  QRect rect = layout_->cellRect(1, 0);
  maxDiameter_ = rect.height();

  setMinScore(min_score);
  setMaxScore(max_score);
  updateScore_ = updateScore;
  scoreLabel_->setText( QString().setNum( competitor_.getScore() ) );

  if ( maxScore_ == 0 ) {
    competitorShape_->setRadius(5);
  } else {
    if ( competitor_.getScore() == maxScore_ ) {
      competitorShape_->setShape(square);
      double radius = (double) maxDiameter_ / 2.0;
      double circleArea = PI * radius * radius;
      competitorShape_->setRadius( (int) sqrt(circleArea) );
    } else {
      competitorShape_->setShape(circle);
      if ( displayMethodology_ == RATIO) {
        updateUsingRatio();
      } else {
        updateUsingRank();
      }
    }
  }

  if ( updateScore_ ) {
    savedScore_ = competitor_.getScore();
  }

  sendUpdate();
}

void CompetitorWidget::updateUsingRatio()
{
  competitorShape_->setShape(circle);
  double ratio = (double) maxScore_ / competitor_.getScore() ;
  double maxRadius = (double) maxDiameter_ / 2.0;
  double radius = ( ratio > 0 ) ? sqrt( (maxRadius * maxRadius ) / ratio ) : 0;
  if ( radius  == 0 ) radius = 5;
  competitorShape_->setRadius( (int) radius );
}

void CompetitorWidget::updateUsingRank()
{
  const Game* game = competitor_.getGame();
  int rank = game->getRank( competitor_.getScore() );
  int competitors = game->getNumberCompetitors();

  int diameter = (double) (competitors - rank) / competitors * maxDiameter_;
  competitorShape_->setRadius( (int) diameter / 2);
}
