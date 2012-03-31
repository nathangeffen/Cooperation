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
