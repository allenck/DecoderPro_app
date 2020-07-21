#ifndef LAYOUTDOUBLESLIP_H
#define LAYOUTDOUBLESLIP_H
#include "layoutslip.h"

class LayoutDoubleSlip : public LayoutSlip
{
  Q_OBJECT
 public:
  /*public*/ LayoutDoubleSlip(QString id, QPointF c, double rot, LayoutEditor* layoutEditor);

};

#endif // LAYOUTDOUBLESLIP_H
