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
