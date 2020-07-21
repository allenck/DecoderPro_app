#ifndef POSITIONABLEPOINTVIEW_H
#define POSITIONABLEPOINTVIEW_H
#include "layouttrackview.h"
#include "positionablepoint.h"

class PositionablePointView : public LayoutTrackView
{
  Q_OBJECT
 public:
  /*public*/ PositionablePointView(/*@Nonnull*/ PositionablePoint* point);

 private:
  /*final*/ /*private*/ PositionablePoint* positionablePoint;
 protected:
  /*protected*/ void draw1(EditScene *g2, bool isMain, bool isBlock);

  friend class LayoutEditorComponent;
};

#endif // POSITIONABLEPOINTVIEW_H
