#ifndef LAYOUTLHTURNOUTEDITOR_H
#define LAYOUTLHTURNOUTEDITOR_H
#include "layoutturnouteditor.h"

class LayoutEditor;
class LayoutLHTurnoutEditor : public LayoutTurnoutEditor
{
  Q_OBJECT
 public:
  /*public*/ LayoutLHTurnoutEditor(/*@Nonnull*/ LayoutEditor* layoutEditor);


 protected:
  /*protected*/ void setContinuingRouteTurnoutState();

};

#endif // LAYOUTLHTURNOUTEDITOR_H
