#ifndef COMPETITORSHAPE_H
#define COMPETITORSHAPE_H

#include <QWidget>

class QColor;

enum Shape {
  square,
  circle,
  sphere
};

class CompetitorShape : public QWidget
{
    Q_OBJECT
public:
  CompetitorShape(int initialLength, QColor& color, QWidget *parent = 0);
  void setRadius( int radius ) { radius_ = radius; }
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
