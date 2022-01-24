#ifndef LAYOUTRHXOVERVIEW_H
#define LAYOUTRHXOVERVIEW_H
#include "layoutxoverview.h"
#include "layoutrhxover.h"

class LayoutRHXOverView : public LayoutXOverView
{
  Q_OBJECT
 public:
  /*public*/ LayoutRHXOverView(/*@Nonnull*/ LayoutRHXOver* xover,
         /*@Nonnull*/ QPointF c, double rot,
         double xFactor, double yFactor,
         /*@Nonnull*/ LayoutEditor* layoutEditor);


};

#endif // LAYOUTRHXOVERVIEW_H
