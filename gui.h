#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include "game/common.h"

class Game;

/** Small wrapper class to start the GUI for a particular game.
  *
  */

class Gui
{
public:
  Gui( Game& game );
  int start();
private:
  Game& game_;
};


#endif // GUI_H
