#ifndef LAYOUTTURNTABLEVIEW_H
#define LAYOUTTURNTABLEVIEW_H
#include "layouttrackview.h"
#include "layoutturntable.h"

class LayoutTurntableView : public LayoutTrackView
{
 public:
  /*public*/ LayoutTurntableView(/*@Nonnull*/ LayoutTurntable* turntable);

 private:
  /*final*/ /*private*/ LayoutTurntable* turntable;

 protected:
  /*protected*/ void drawTurnoutControls(EditScene *g2);

};

#endif // LAYOUTTURNTABLEVIEW_H
