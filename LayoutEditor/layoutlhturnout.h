#ifndef LAYOUTLHTURNOUT_H
#define LAYOUTLHTURNOUT_H
#include "layoutturnout.h"

class LayoutLHTurnout : public LayoutTurnout
{
  Q_OBJECT
 public:
  /*public*/ LayoutLHTurnout(/*@Nonnull*/ QString id,
          /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutLHTurnout(/*@Nonnull*/ QString id, /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor, /*@Nonnull*/ LayoutEditor* layoutEditor, int v);

};

#endif // LAYOUTLHTURNOUT_H
