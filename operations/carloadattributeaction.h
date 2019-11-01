#ifndef CARLOADATTRIBUTEACTION_H
#define CARLOADATTRIBUTEACTION_H
#include "abstractaction.h"

class Logger;
namespace Operations
{
 class CarLoadEditFrame;
 class CarLoadAttributeAction : public AbstractAction
 {
  Q_OBJECT
 public:
  CarLoadAttributeAction(QString actionName, CarLoadEditFrame* clef);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* ae = 0);
 private:
  CarLoadEditFrame* clef;
  Logger* log;
 };
}
#endif // CARLOADATTRIBUTEACTION_H
