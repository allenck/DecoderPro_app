#ifndef TRAINSSCRIPTACTION_H
#define TRAINSSCRIPTACTION_H
#include "abstractaction.h"

namespace Operations
{
 class TrainsScriptFrame;
 class TrainsTableFrame;
 class TrainsScriptAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrainsScriptAction(QString s, TrainsTableFrame* frame);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0);
 private:
  TrainsTableFrame* frame; // the parent frame that is launching the TrainScriptFrame.
  TrainsScriptFrame* f = nullptr;
 };
}
#endif // TRAINSSCRIPTACTION_H
