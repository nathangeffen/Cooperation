#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include "common.h"

class Game;

class Gui
{
public:
  Gui( Game& game );
  int start();
private:
  Game& game_;
};


#endif // GUI_H
