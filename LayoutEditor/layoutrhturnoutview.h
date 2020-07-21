#ifndef LAYOUTRHTURNOUTVIEW_H
#define LAYOUTRHTURNOUTVIEW_H
#include "layoutturnoutview.h"
#include "layoutrhturnout.h"

class LayoutRHTurnoutView : public LayoutTurnoutView
{
  Q_OBJECT
 public:
  /*public*/ LayoutRHTurnoutView(/*@Nonnull*/ LayoutRHTurnout* turnout);

};

#endif // LAYOUTRHTURNOUTVIEW_H
