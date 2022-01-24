#ifndef LAYOUTWYE_H
#define LAYOUTWYE_H
#include "layoutturnout.h"

class LayoutWye : public LayoutTurnout
{
  Q_OBJECT
 public:
  /*public*/ LayoutWye(/*@Nonnull*/ QString id,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutWye(/*@Nonnull*/ QString id,  LayoutEditor* layoutEditor, int v);

};

#endif // LAYOUTWYE_H
