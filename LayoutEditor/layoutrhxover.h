#ifndef LAYOUTRHXOVER_H
#define LAYOUTRHXOVER_H
#include "layoutxover.h"

class LayoutRHXOver : public LayoutXOver
{
  Q_OBJECT
 public:
  /*public*/ LayoutRHXOver(/*@Nonnull*/ QString id,
          /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutRHXOver(/*@Nonnull*/ QString id, /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor, /*@Nonnull*/ LayoutEditor* layoutEditor, int v);

};

#endif // LAYOUTRHXOVER_H
