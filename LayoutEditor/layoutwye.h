#ifndef LAYOUTWYE_H
#define LAYOUTWYE_H
#include "layoutturnout.h"

class LayoutWye : public LayoutTurnout
{
  Q_OBJECT
 public:
  /*public*/ LayoutWye(/*@Nonnull*/ QString id,
          /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutWye(/*@Nonnull*/ QString id, /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor, /*@Nonnull*/ LayoutEditor* layoutEditor, int v);

};

#endif // LAYOUTWYE_H
