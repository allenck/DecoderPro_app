#ifndef SHOWCARSINTRAINACTION_H
#define SHOWCARSINTRAINACTION_H

#include "abstractaction.h"
namespace Operations
{
 class Train;
 class ShowCarsInTrainFrame;
 class ShowCarsInTrainAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ShowCarsInTrainAction(QString s, Train* train,QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e);
 private:
  ShowCarsInTrainFrame* f;// = null;
  Train* train;

 };
}
#endif // SHOWCARSINTRAINACTION_H
