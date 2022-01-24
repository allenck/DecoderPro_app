#ifndef SHOWCARSINTRAINACTION_H
#define SHOWCARSINTRAINACTION_H

#include "abstractaction.h"
#include "showcarsintrainframe.h"
#include <QPointer>

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
  /*public*/ void actionPerformed(JActionEvent * /*e*/);
 private:
  QPointer<ShowCarsInTrainFrame> f;// = null;
  Train* train;

 };
}
#endif // SHOWCARSINTRAINACTION_H
