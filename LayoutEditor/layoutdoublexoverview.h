#ifndef LAYOUTDOUBLEXOVERVIEW_H
#define LAYOUTDOUBLEXOVERVIEW_H
#include "layoutxoverview.h"
#include "layoutdoublexover.h"

class LayoutDoubleXOverView : public LayoutXOverView
{
 public:
  /*public*/ LayoutDoubleXOverView(/*@Nonnull*/ LayoutDoubleXOver* xover,
                                /*@Nonnull*/ QPointF c, double rot,
                                double xFactor, double yFactor,
                                /*@Nonnull*/ LayoutEditor* layoutEditor);


};

#endif // LAYOUTDOUBLEXOVERVIEW_H
