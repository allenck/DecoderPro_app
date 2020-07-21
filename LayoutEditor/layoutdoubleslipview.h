#ifndef LAYOUTDOUBLESLIPVIEW_H
#define LAYOUTDOUBLESLIPVIEW_H
#include "layoutslipview.h"
#include "layoutdoubleslip.h"

class LayoutDoubleSlipView : public LayoutSlipView
{
  Q_OBJECT
 public:
  LayoutDoubleSlipView(/*@Nonnull*/ LayoutDoubleSlip* slip);
};

#endif // LAYOUTDOUBLESLIPVIEW_H
