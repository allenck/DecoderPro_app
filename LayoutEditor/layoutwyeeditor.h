#ifndef LAYOUTWYEEDITOR_H
#define LAYOUTWYEEDITOR_H
#include "layoutturnouteditor.h"

class LayoutWyeEditor : public LayoutTurnoutEditor
{
  Q_OBJECT
 public:
  /*public*/ LayoutWyeEditor(/*@Nonnull*/ LayoutEditor* layoutEditor);

 protected:
  /*protected*/ void setContinuingRouteTurnoutState();

};

#endif // LAYOUTWYEEDITOR_H
