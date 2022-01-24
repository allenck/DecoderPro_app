#ifndef LAYOUTDOUBLESLIPVIEW_H
#define LAYOUTDOUBLESLIPVIEW_H
#include "layoutslipview.h"
#include "layoutdoubleslip.h"

class LayoutDoubleSlipView : public LayoutSlipView
{
  Q_OBJECT
 public:
  /*public*/ LayoutDoubleSlipView(/*@Nonnull*/ LayoutDoubleSlip* slip, QPointF c, double rot, /*@Nonnull*/ LayoutEditor* layoutEditor);

};

#endif // LAYOUTDOUBLESLIPVIEW_H
