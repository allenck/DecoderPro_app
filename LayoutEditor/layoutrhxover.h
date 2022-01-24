#ifndef LAYOUTRHXOVER_H
#define LAYOUTRHXOVER_H
#include "layoutxover.h"

class LayoutRHXOver : public LayoutXOver
{
  Q_OBJECT
 public:
  /*public*/ LayoutRHXOver(/*@Nonnull*/ QString id,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutRHXOver(/*@Nonnull*/ QString id,  LayoutEditor* layoutEditor, int v);

};

#endif // LAYOUTRHXOVER_H
