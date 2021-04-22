#ifndef LAYOUTLHTURNOUTVIEW_H
#define LAYOUTLHTURNOUTVIEW_H
#include "layoutturnoutview.h"
#include "layoutlhturnout.h"

class LayoutLHTurnoutView : public LayoutTurnoutView
{
  Q_OBJECT
 public:
  /*public*/ LayoutLHTurnoutView(/*@Nonnull*/ LayoutLHTurnout* turnout,
                              /*@Nonnull*/ QPointF c, double rot,
                              double xFactor, double yFactor,
                              /*@Nonnull*/ LayoutEditor* layoutEditor);

};

#endif // LAYOUTLHTURNOUTVIEW_H
