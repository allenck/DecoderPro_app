#ifndef SETTRAINICONPOSITIONACTION_H
#define SETTRAINICONPOSITIONACTION_H
#include "abstractaction.h"

namespace Operations
{
 class SetTrainIconPositionFrame;
 class SetTrainIconPositionAction : public AbstractAction
 {
  Q_OBJECT
 public:
     SetTrainIconPositionAction(QString s, QObject* parent);
 public slots:
     /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
     SetTrainIconPositionFrame* f;// = NULL;

 };
}
#endif // SETTRAINICONPOSITIONACTION_H
