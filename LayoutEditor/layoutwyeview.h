#ifndef LAYOUTWYEVIEW_H
#define LAYOUTWYEVIEW_H
#include "layoutturnoutview.h"
#include "layoutwye.h"

class LayoutWyeView : public LayoutTurnoutView
{
 public:
  /*public*/ LayoutWyeView(/*@Nonnull*/ LayoutWye *wye,
         /*@Nonnull*/ QPointF c, double rot,
         double xFactor, double yFactor,
         /*@Nonnull*/ LayoutEditor* layoutEditor);

};

#endif // LAYOUTWYEVIEW_H
