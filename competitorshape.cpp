#include <QtGui>
#include <QPainter>

#include "competitorshape.h"

CompetitorShape::CompetitorShape(int initialRadius,
                                 QColor& color, QWidget *parent) :
  QWidget(parent), color_(color), shape_(circle)
{
  setRadius(initialRadius);
}


void CompetitorShape::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.setPen(Qt::NoPen);
  painter.setBrush(color_);
  if ( shape_ == square ) {
    int x_cord = ( this->geometry().width() - radius_ ) / 2;
    int y_cord = ( this->geometry().height() - radius_ ) / 2;
    painter.drawRect( x_cord, y_cord, radius_ , radius_ );
  } else {
    int centre_x = this->geometry().width() / 2;
    int centre_y = this->geometry().height() / 2;
    painter.drawEllipse( QPoint(centre_x, centre_y), radius_, radius_ );
  }
}
