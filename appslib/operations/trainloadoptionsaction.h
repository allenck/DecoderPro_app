#ifndef TRAINLOADOPTIONSACTION_H
#define TRAINLOADOPTIONSACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrainEditFrame;
 class TrainLoadOptionsFrame;
 class TrainLoadOptionsAction : public AbstractAction
 {
   Q_OBJECT
 public:
  TrainLoadOptionsAction(QString s, TrainEditFrame* parent);

 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  TrainEditFrame* frame;	// the parent frame that is launching the TrainEditBuildOptionsFrame.

  TrainLoadOptionsFrame* f;// = null;


 };
}
#endif // TRAINLOADOPTIONSACTION_H
