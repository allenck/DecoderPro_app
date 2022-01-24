#ifndef LAYOUTLHXOVER_H
#define LAYOUTLHXOVER_H
#include "layoutxover.h"

class LayoutLHXOver : public LayoutXOver
{
  Q_OBJECT
 public:
  /*public*/ LayoutLHXOver(/*@Nonnull*/ QString id,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutLHXOver(/*@Nonnull*/ QString id, /*@Nonnull*/ LayoutEditor* layoutEditor, int v);

};

#endif // LAYOUTLHXOVER_H
