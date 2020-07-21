#ifndef LAYOUTRHTURNOUTEDITOR_H
#define LAYOUTRHTURNOUTEDITOR_H
#include "layoutturnouteditor.h"
#include "layoutturnout.h"

class LayoutRHTurnoutEditor : public LayoutTurnoutEditor
{
  Q_OBJECT
 public:
  /*public*/ LayoutRHTurnoutEditor(/*@Nonnull*/ LayoutEditor* layoutEditor);
 protected:
  /*protected*/ void setContinuingRouteTurnoutState();

};

#endif // LAYOUTRHTURNOUTEDITOR_H
