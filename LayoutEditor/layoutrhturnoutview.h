#ifndef LAYOUTRHTURNOUTVIEW_H
#define LAYOUTRHTURNOUTVIEW_H
#include "layoutturnoutview.h"
#include "layoutrhturnout.h"

class LayoutRHTurnoutView : public LayoutTurnoutView
{
  Q_OBJECT
 public:
  /*public*/ LayoutRHTurnoutView(/*@Nonnull*/ LayoutRHTurnout* turnout,
    /*@Nonnull*/ QPointF c, double rot,
    double xFactor, double yFactor,
    /*@Nonnull*/ LayoutEditor* layoutEditor);


};

#endif // LAYOUTRHTURNOUTVIEW_H
