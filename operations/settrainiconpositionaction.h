#ifndef SETTRAINICONPOSITIONACTION_H
#define SETTRAINICONPOSITIONACTION_H
#include "abstractaction.h"
#include "settrainiconpositionframe.h"
#include <QPointer>

namespace Operations
{
 class SetTrainIconPositionFrame;
 class SetTrainIconPositionAction : public AbstractAction
 {
  Q_OBJECT
 public:
     SetTrainIconPositionAction( QObject* parent);
 public slots:
     /*public*/ void actionPerformed(JActionEvent* e = 0);

 private:
     QPointer<SetTrainIconPositionFrame> f;// = NULL;

 };
}
#endif // SETTRAINICONPOSITIONACTION_H
