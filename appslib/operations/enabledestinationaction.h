#ifndef ENABLEDESTINATIONACTION_H
#define ENABLEDESTINATIONACTION_H

#include "abstractaction.h"
namespace Operations
{
 class CarSetFrame;
 class EnableDestinationAction : public AbstractAction
 {
  Q_OBJECT
 public:
  EnableDestinationAction(QString s, CarSetFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  CarSetFrame* _csFrame;

 };
}
#endif // ENABLEDESTINATIONACTION_H
