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

#ifndef COMPETITORSHAPE_H
#define COMPETITORSHAPE_H

#include <QWidget>

class QColor;

/** Competitors are drawn as a circle but the leading competitor is drawn as a
  * square.
  *
  * A sphere shape has been defined for future use.
  */
enum Shape {
  square,
  circle,
  sphere
};

/** Class responsible for managing the shape of a competitor.
  *
  */

class CompetitorShape : public QWidget
{
    Q_OBJECT
public:

  /** Constructor that sets the initial radius of the shape and its color.
    */
  CompetitorShape(int initialRadius, QColor& color, QWidget *parent = 0);

  /** Sets a new radius for the shape.
    */
  void setRadius( int radius ) { radius_ = radius; }

  /** Changes the competitor's shape to the shape specified in the parameter.
    */
  void setShape(Shape shape) { shape_ = shape; }

signals:

public slots:
  void executeUpdate() { update(); }

protected:
  void paintEvent(QPaintEvent *);

private:
  QColor& color_;
  int radius_;
  Shape shape_;
};

#endif // COMPETITORSHAPE_H
