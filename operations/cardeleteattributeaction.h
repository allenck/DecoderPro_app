#ifndef CARDELETEATTRIBUTEACTION_H
#define CARDELETEATTRIBUTEACTION_H
#include "abstractaction.h"
#include "appslib_global.h"

class Logger;
namespace Operations
{
 class CarAttributeEditFrame;
 class APPSLIBSHARED_EXPORT CarDeleteAttributeAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ CarDeleteAttributeAction(QString actionName, CarAttributeEditFrame* caef);
  public slots:
  /*public*/ void actionPerformed(ActionEvent* ae = 0);
 private:
  CarAttributeEditFrame* caef;
  Logger* log;
 };
}
#endif // CARDELETEATTRIBUTEACTION_H
