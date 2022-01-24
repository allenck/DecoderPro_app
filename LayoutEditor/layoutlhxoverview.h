#ifndef LAYOUTLHXOVERVIEW_H
#define LAYOUTLHXOVERVIEW_H
#include "layoutxoverview.h"
#include "layoutlhxover.h"

class LayoutLHXOverView : public LayoutXOverView
{
 public:
  /*public*/ LayoutLHXOverView(/*@Nonnull*/ LayoutLHXOver* xover,
         /*@Nonnull*/ QPointF c, double rot,
         double xFactor, double yFactor,
         /*@Nonnull*/ LayoutEditor* layoutEditor);

};

#endif // LAYOUTLHXOVERVIEW_H
