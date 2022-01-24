#ifndef TRAINSSCRIPTACTION_H
#define TRAINSSCRIPTACTION_H
#include "abstractaction.h"
#include "trainsscriptframe.h"
#include "trainstableframe.h"
#include <QPointer>

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
  QPointer<TrainsTableFrame> frame; // the parent frame that is launching the TrainScriptFrame.
  QPointer<TrainsScriptFrame> f = nullptr;
 };
}
#endif // TRAINSSCRIPTACTION_H
