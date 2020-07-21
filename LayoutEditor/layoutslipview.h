#ifndef LAYOUTSLIPVIEW_H
#define LAYOUTSLIPVIEW_H
#include "layoutturnoutview.h"
#include "layoutslip.h"

class LayoutSlipView : public LayoutTurnoutView
{
  Q_OBJECT
 public:
  /*public*/ LayoutSlipView(/*@Nonnull*/ LayoutSlip* slip);

};

#endif // LAYOUTSLIPVIEW_H
