#include <QLabel>
#include "competitor.h"
#include "competitorwidget.h"

CompetitorWidget::CompetitorWidget(int circleSize, Competitor& competitor,
                                   QWidget *parent) :
  QWidget(parent), circleSize_(circleSize),
  competitor_(competitor), maxScore_(0)
{
  color_ = competitor.getColor();
  label = new QLabel;
  label->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

}

void CompetitorWidget::paintEvent(QPaintEvent *)
{ 
  QPainter painter(this);
  painter.setBrush(QColor(color_));

  label->setText( competitor_.output() + competitor_.getScore() );
  if ( maxScore_ == 0 ) {
    painter.drawEllipse(0, 0, 5, 5);
  } else {
    int circleSize = (double) ( competitor_.getScore() - minScore_) /
                     (double) (maxScore_ - minScore_) * circleSize_;
    if ( circleSize == 0 ) circleSize = 5;
    painter.drawEllipse(0, 0, circleSize, circleSize);
  }
}
