#ifndef LAYOUTDOUBLEXOVER_H
#define LAYOUTDOUBLEXOVER_H
#include "layoutxover.h"

class LayoutDoubleXOver : public LayoutXOver
{
  Q_OBJECT
 public:
  /*public*/ LayoutDoubleXOver(/*@Nonnull*/ QString id,
          /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutDoubleXOver(/*@Nonnull*/ QString id, /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor, /*@Nonnull*/ LayoutEditor* layoutEditor, int v);
};

#endif // LAYOUTDOUBLEXOVER_H
