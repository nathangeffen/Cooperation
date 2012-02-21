#include <QVBoxLayout>
#include <QLabel>
#include "competitor.h"
#include "competitorwidget.h"

CompetitorWidget::CompetitorWidget(int maxCircleSize, Competitor& competitor,
                                   QWidget *parent) :
  QWidget(parent), competitor_(competitor),
  maxCircleSize_(maxCircleSize / 2 - 5), maxScore_(0), savedScore_(0)
{
  color_ = competitor.getColor();
}

void CompetitorWidget::paintEvent(QPaintEvent *)
{ 
  QPainter painter(this);

  painter.setBrush(QColor(color_));

  if ( maxScore_ == 0 ) {
    painter.drawEllipse(0, maxCircleSize_, maxCircleSize_ / 2, maxCircleSize_ / 2);
  } else {
    if ( competitor_.getScore() == maxScore_ ) {
      painter.drawRect(0, maxCircleSize_, maxCircleSize_, maxCircleSize_);
    } else {
      int circleSize = ( (double) competitor_.getScore() / maxScore_ ) * maxCircleSize_;
      if ( circleSize == 0 ) circleSize = 5;
      painter.drawEllipse( 0, maxCircleSize_, circleSize, circleSize );
    }
    if ( updateScore_ ) {
      savedScore_ = competitor_.getScore();
    }
  }
  painter.setPen(Qt::SolidLine);
  painter.drawText( 0, 15, competitor_.output() );
  painter.drawText( maxCircleSize_ , 35, QString().setNum( savedScore_ ) );
}
