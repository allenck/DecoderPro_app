#ifndef LAYOUTXOVER_H
#define LAYOUTXOVER_H
#include "layoutturnout.h"

class LayoutXOver : public LayoutTurnout
{
  Q_OBJECT
 public:
  /*public*/ LayoutXOver(/*@Nonnull*/ QString id, TurnoutType t,  /*@Nonnull*/ LayoutEditor* layoutEditor, int v);

};

#endif // LAYOUTXOVER_H
