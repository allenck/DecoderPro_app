#ifndef CHANGEDEPARTURETIMESACTION_H
#define CHANGEDEPARTURETIMESACTION_H

#include "abstractaction.h"
namespace Operations
{
 class ChangeDepartureTimesFrame;
 class ChangeDepartureTimesAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ChangeDepartureTimesAction(QString s,QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  ChangeDepartureTimesFrame* f;// = null;

 };
}
#endif // CHANGEDEPARTURETIMESACTION_H
