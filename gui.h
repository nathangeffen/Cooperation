#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include "common.h"

class Game;

class Gui
{
public:
  Gui( Game& game, DisplayMethodology displaymethodology );
  int start();
private:
  Game& game_;
  DisplayMethodology displayMethodology_;
};


#endif // GUI_H
