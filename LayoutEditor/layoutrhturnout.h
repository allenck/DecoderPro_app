#ifndef LAYOUTRHTURNOUT_H
#define LAYOUTRHTURNOUT_H
#include "layoutturnout.h"

class LayoutRHTurnout : public LayoutTurnout
{
  Q_OBJECT
 public:
  /*public*/ LayoutRHTurnout(/*@Nonnull*/ QString id,
          /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutRHTurnout(/*@Nonnull*/ QString id, /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor, /*@Nonnull*/ LayoutEditor* layoutEditor, int v);

};

#endif // LAYOUTRHTURNOUT_H
