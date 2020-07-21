#ifndef LAYOUTSINGLESLIP_H
#define LAYOUTSINGLESLIP_H
#include "layoutslip.h"

class LayoutSingleSlip : public LayoutSlip
{
  Q_OBJECT
 public:
  /*public*/ LayoutSingleSlip(QString id, QPointF c, double rot, LayoutEditor* layoutEditor);

};

#endif // LAYOUTSINGLESLIP_H
