#ifndef TRAINSSCRIPTACTION_H
#define TRAINSSCRIPTACTION_H
#include "abstractaction.h"

namespace Operations
{
 class TrainsTableFrame;
 class TrainsScriptAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrainsScriptAction(QString s, TrainsTableFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  TrainsTableFrame* frame; // the parent frame that is launching the TrainScriptFrame.

 };
}
#endif // TRAINSSCRIPTACTION_H
