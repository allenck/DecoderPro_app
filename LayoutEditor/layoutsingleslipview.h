#ifndef LAYOUTSINGLESLIPVIEW_H
#define LAYOUTSINGLESLIPVIEW_H
#include "layoutslipview.h"
#include "layoutsingleslip.h"

class LayoutSingleSlipView : public LayoutSlipView
{
  Q_OBJECT
 public:
  /*public*/ LayoutSingleSlipView(/*@Nonnull*/ LayoutSingleSlip* slip);

};

#endif // LAYOUTSINGLESLIPVIEW_H
