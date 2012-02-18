#include "competitorwidget.h"

CompetitorWidget::CompetitorWidget(int circleSize, QString color, QWidget *parent) :
  QWidget(parent), circleSize_(circleSize), color_(color)
{}

void CompetitorWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setBrush(QColor(color_));
  painter.drawEllipse(0,0, circleSize_, circleSize_);
}
