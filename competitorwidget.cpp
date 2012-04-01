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

#include <cmath>
#include <QGridLayout>
#include <QLabel>
#include "game/game.h"
#include "game/competitor.h"
#include "competitorwidget.h"
#include "competitorshape.h"
#include "game/common.h"

CompetitorWidget::CompetitorWidget(int maxDiameter,
                                   Competitor& competitor,
                                   DisplayMethodology displayMethodology,
                                   QColor color,
                                   QWidget *parent) :
  QWidget(parent), competitor_(competitor),
  maxDiameter_(maxDiameter ), maxScore_(0), savedScore_(0),
  displayMethodology_(displayMethodology), color_(color)
{
  nameLabel_ = new QLabel( competitor_.output().toUpper(), this );
  QFont font = nameLabel_->font();
  font.setPointSize(6);

  nameLabel_->setFont(font);

  scoreLabel_ = new QLabel( QString().setNum(0), this );
  scoreLabel_->setFont(font);

  topline_ = new QHBoxLayout();
  topline_->addWidget(nameLabel_);
  topline_->addWidget(scoreLabel_);

  layout_ = new QGridLayout();
  layout_->addLayout(topline_, 0, 0);
  layout_->setRowStretch(0, 1);

  competitorShape_ = new CompetitorShape(maxDiameter / 6,
                                         color_);
  layout_->addWidget(competitorShape_, 1, 0);
  layout_->setRowStretch(1, 10);

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
      } else if ( displayMethodology_ == RANK ){
        updateUsingRank();
      } else {
        updateUsingRatioNormalizedToZero();
      }
    }
  }

  if ( updateScore_ ) {
    savedScore_ = competitor_.getScore();
  }

  competitorShape_->executeUpdate();
}

void CompetitorWidget::updateUsingRatio()
{
  competitorShape_->setShape(circle);
  double ratio = (double) maxScore_ / competitor_.getScore() ;
  double maxRadius = (double) maxDiameter_ / 2.0;
  double radius = ( ratio > 0 ) ? sqrt( (maxRadius * maxRadius ) / ratio ) : 0;
  if ( radius  < 3 ) radius = 3;
  competitorShape_->setRadius( (int) radius );
}

void CompetitorWidget::updateUsingRatioNormalizedToZero()
{
  competitorShape_->setShape(circle);
  double ratio = (double) (maxScore_ - minScore_) /
                 ( competitor_.getScore() - minScore_ + 1) ;
  double maxRadius = (double) maxDiameter_ / 2.0;
  double radius = ( ratio > 0 ) ? sqrt( (maxRadius * maxRadius ) / ratio ) : 0;
  if ( radius  < 3 ) radius = 3;
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

