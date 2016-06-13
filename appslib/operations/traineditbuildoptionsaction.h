#ifndef TRAINEDITBUILDOPTIONSACTION_H
#define TRAINEDITBUILDOPTIONSACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrainEditFrame;
 class TrainEditBuildOptionsFrame;
 class TrainEditBuildOptionsAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ TrainEditBuildOptionsAction(QString s, TrainEditFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  TrainEditBuildOptionsFrame* f;// = null;
  TrainEditFrame* frame;	// the parent frame that is launching the TrainEditBuildOptionsFrame.

 };
}
#endif // TRAINEDITBUILDOPTIONSACTION_H
