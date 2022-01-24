#ifndef CHANGEDEPARTURETIMESACTION_H
#define CHANGEDEPARTURETIMESACTION_H

#include "abstractaction.h"
#include "changedeparturetimesframe.h"
#include <QPointer>

namespace Operations
{
 class ChangeDepartureTimesFrame;
 class ChangeDepartureTimesAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ChangeDepartureTimesAction(QString s,QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0);
 private:
  QPointer<ChangeDepartureTimesFrame> f;// = null;

 };
}
#endif // CHANGEDEPARTURETIMESACTION_H
