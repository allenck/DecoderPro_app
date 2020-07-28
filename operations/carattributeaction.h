#ifndef CARATTRIBUTEACTION_H
#define CARATTRIBUTEACTION_H
#include "abstractaction.h"
#include "appslib_global.h"

class Logger;
namespace Operations
{
 class CarAttributeEditFrame;
 class APPSLIBSHARED_EXPORT CarAttributeAction : public AbstractAction
 {
  Q_OBJECT
  CarAttributeEditFrame* caef;
  Logger* log;
 public:
  /*public*/ CarAttributeAction( CarAttributeEditFrame* caef);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* ae = 0);

 };
}
#endif // CARATTRIBUTEACTION_H
