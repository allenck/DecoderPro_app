#ifndef TRAINSCRIPTACTION_H
#define TRAINSCRIPTACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrainScriptFrame;
 class TrainEditFrame;
 class TrainScriptAction : public AbstractAction
 {
 public:
  TrainScriptAction(QString s, TrainEditFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  TrainScriptFrame* f;// = null;
  TrainEditFrame* frame;	// the parent frame that is launching the TrainScriptFrame.

 };
}
#endif // TRAINSCRIPTACTION_H
