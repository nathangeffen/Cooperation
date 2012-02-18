#include <QApplication>
#include <QObject>
#include <QtGui>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>

#include "game.h"
#include "gui.h"
#include "competitorwidget.h"


class GameLayout : public QWidget
{
public:
  GameLayout(Game& game, QWidget *parent = 0);
private:
  Game& game_;
};

GameLayout::GameLayout(Game& game, QWidget *parent)
  : QWidget(parent), game_(game)
{
  QPushButton *quit = new QPushButton(tr("&Quit"));
  quit->setFont(QFont("Times", 18, QFont::Bold));
  connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

  QGridLayout *playerSection = new QGridLayout;

  QGridLayout *topLayout = new QGridLayout;
  topLayout->addWidget(quit, 0, 0);
  topLayout->addLayout(playerSection, 1, 0);
  setLayout(topLayout);
  QRect screenSize = QApplication::desktop()->availableGeometry();
  this->setGeometry(screenSize);


  int square;
  for (square = 0; square * square < game_.getNumberCompetitors(); square++ );

  int max_height = this->geometry().height() - 100;
  int circleSize = max_height / square;
  qDebug() << max_height << square << circleSize;

  int counter = 0;
  for ( int i=0; i < square && counter < game_.getNumberCompetitors(); i++ ) {
    for (int j = 0; j < square && counter < game_.getNumberCompetitors(); j++) {
      CompetitorWidget *competitorWidget = new
          CompetitorWidget(circleSize,
                           game_.getCompetitor(counter).getColor() );
      playerSection->addWidget(competitorWidget, i, j);
      ++counter;
    }
  }

}

Gui::Gui( Game& game ) : game_(game) {}

int Gui::execute()
{
  int argc = 0;
  char *argv[] = {};
  QApplication app(argc, argv);
  GameLayout widget(game_);
  widget.show();

  return app.exec();
}

