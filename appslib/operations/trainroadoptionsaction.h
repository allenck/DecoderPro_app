#ifndef TRAINROADOPTIONSACTION_H
#define TRAINROADOPTIONSACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrainEditFrame;
 class TrainRoadOptionsFrame;
 class TrainRoadOptionsAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrainRoadOptionsAction(QString s, TrainEditFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  TrainEditFrame* frame;	// the parent frame that is launching the TrainEditBuildOptionsFrame.

  TrainRoadOptionsFrame* f;// = null;

 };
}
#endif // TRAINROADOPTIONSACTION_H
