#ifndef LAYOUTLHTURNOUTVIEW_H
#define LAYOUTLHTURNOUTVIEW_H
#include "layoutturnoutview.h"
#include "layoutlhturnout.h"

class LayoutLHTurnoutView : public LayoutTurnoutView
{
  Q_OBJECT
 public:
  /*public*/ LayoutLHTurnoutView(/*@Nonnull*/ LayoutLHTurnout* turnout);

};

#endif // LAYOUTLHTURNOUTVIEW_H
