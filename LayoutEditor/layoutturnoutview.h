#ifndef LAYOUTTURNOUTVIEW_H
#define LAYOUTTURNOUTVIEW_H
#include "layouttrackview.h"

class LayoutTurnoutView : public LayoutTrackView
{
  Q_OBJECT
 public:
  /*public*/ LayoutTurnoutView(/*@Nonnull*/ LayoutTurnout* turnout);
  /*public*/ QPointF getCoordsA();
  /*public*/ QPointF getCoordsB() ;
  /*public*/ QPointF getCoordsC();
  /*public*/ QPointF getCoordsD();
  /*public*/ bool isMainlineA();
  /*public*/ bool isMainlineB();
  /*public*/ bool isMainlineC();
  /*public*/ bool isMainlineD();


 private:
  /*final*/ /*private*/ LayoutTurnout* turnout;

 protected:
  /*protected*/ bool isDisabled();
  /*protected*/ void drawTurnoutControls(EditScene* g2);

};

#endif // LAYOUTTURNOUTVIEW_H
