#ifndef LAYOUTRHTURNOUT_H
#define LAYOUTRHTURNOUT_H
#include "layoutturnout.h"

class LayoutRHTurnout : public LayoutTurnout
{
  Q_OBJECT
 public:
  /*public*/ LayoutRHTurnout(/*@Nonnull*/ QString id, /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutRHTurnout(/*@Nonnull*/ QString id, /*@Nonnull*/ LayoutEditor* layoutEditor, int v);

};

#endif // LAYOUTRHTURNOUT_H
