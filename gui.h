#ifndef GUI_H
#define GUI_H

#include <QWidget>

class Game;

class Gui
{
public:
  Gui( Game& game );
  int execute();
private:
  Game& game_;
};


#endif // GUI_H
